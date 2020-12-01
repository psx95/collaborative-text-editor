//
// Created by psx95 on 11/27/20.
//

#include <CustomMessageException.hpp>
#include "UDPClient.hpp"
#include<iostream>

UDPClient::UDPClient(unsigned short port, std::vector<struct PeerAddress> &peer_addresses) {
  this->client_port = port;
  this->peer_addresses = peer_addresses;
  for (PeerAddress peer: peer_addresses) {
    std::cout << peer.ip_address << "\t" << peer.port << std::endl;
  }
  Init();
}

void UDPClient::Init() {
  // Bind socket to port
  client_socket.bind(this->client_port);
  client_socket.setBlocking(false);
  // Initialize socket
  std::thread ListeningThread(&UDPClient::StartListeningThread, this);
  thread_vector.push_back(std::move(ListeningThread));
}

void UDPClient::StartListeningThread() {
  std::cout << "Listening " << std::endl;
  client_listening.store(true, std::memory_order_relaxed);

  while (client_listening.load(std::memory_order_relaxed)) {
    sf::Packet packet;
    sf::IpAddress sender;
    unsigned short port;
    sf::Socket::Status status;
    status = client_socket.receive(packet, sender, port);

    if (status == sf::Socket::Status::Done) {
      this->HandleIncomingPacket(packet);
    }
  }
  std::cout << "Listening terminated" << std::endl;
}

void UDPClient::HandleOutgoingPacket(sf::Packet packet, PeerAddress peer_address) {
  sf::Socket::Status status = client_socket.send(packet, peer_address.ip_address, peer_address.port);
  std::cout << "Send status " << status << std::endl;
}

void UDPClient::BroadcastActionToAllConnectedPeers(CRDTAction &crdt_action) {
  sf::Packet packet;
  packet << crdt_action.Operation() << crdt_action.SiteId() << crdt_action.Counter() << crdt_action.Text() <<
         (int) crdt_action.Positions().size();

  for (long position:crdt_action.Positions()) {
    packet << (sf::Int64)position;
  }

  for (PeerAddress peer_address: this->peer_addresses) {
    std::cout << "Broadcast - " << peer_address.ip_address << "\t" << "port" << peer_address.port << std::endl;

    std::thread HandleOutgoingPacketThread(&UDPClient::HandleOutgoingPacket, this, packet, peer_address);
    thread_vector.push_back(std::move(HandleOutgoingPacketThread));
  }
}

void UDPClient::HandleIncomingPacket(sf::Packet &packet) {
  int operation;
  std::string site_id; // unique id of the client
  int counter; // site counter managed by version vector
  std::string text; // value of the string (current support for single chars) to be inserted.
  int positions_size;
  std::vector<long> positions; // fractional position calculated by CRDT.

  packet >> operation >> site_id >> counter >> text >> positions_size;

  for (int i = 0; i < positions_size; i++) {
    sf::Int64 position;
    packet >> position;
    positions.push_back((long)position);
  }
  CRDTAction crdt_action((CRDTOperation) operation, site_id, counter, text, positions);
  crdt_action.Print();
  client_callbacks->OnRemoteOperationReceive(crdt_action);
}

void UDPClient::ShutdownClient() {
  client_listening.store(false, std::memory_order_relaxed);
  for (auto &th : thread_vector) {
    th.join();
  }
}

void UDPClient::SetClientCallbacks(NetworkingCallbacks *callbacks) {
  if (!callbacks) {
    throw CustomMessageException("NetworkingCallbacks cannot be set as null!");
  }
  this->client_callbacks = callbacks;
}
