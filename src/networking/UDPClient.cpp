//
// Created by psx95 on 11/27/20.
//

#include <iostream>
#include <CustomMessageException.hpp>
#include "UDPClient.hpp"

UDPClient::UDPClient(unsigned short port, std::vector<struct PeerAddress> &peer_addresses) {
  this->client_port = port;
  this->peer_addresses = peer_addresses;
  Init();
}

void UDPClient::Init() {
  client_socket.bind(this->client_port);
  client_socket.setBlocking(false); //make socket non-blocking
  std::thread listeningThread(&UDPClient::StartListeningThread, this);
  listeningThread.detach();
}

void UDPClient::StartListeningThread() {
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
}

void UDPClient::HandleOutgoingPacket(sf::Packet packet, PeerAddress peer_address) {
  sf::Socket::Status status = client_socket.send(packet, peer_address.ip_address, peer_address.port);

  if (status != sf::Socket::Status::Done) {
    std::cerr << "Broadcast Error" << "\t" << status << "\t" << "ip" << "\t" << peer_address.ip_address << "port"
              << "\t" << peer_address.port;
  }
}

void UDPClient::BroadcastActionToAllConnectedPeers(CRDTAction &crdt_action, std::string &site_id, int site_counter) {
  sf::Packet packet;
  packet << crdt_action.Operation() << crdt_action.SiteId() << crdt_action.Counter() << crdt_action.Text() <<
         (int) crdt_action.Positions().size();

  for (long position:crdt_action.Positions()) {
    packet << (sf::Int64) position;
  }
  packet << site_id << site_counter;

  for (PeerAddress peer_address: this->peer_addresses) {
    std::thread handleOutgoingPacketThread(&UDPClient::HandleOutgoingPacket, this, packet, peer_address);
    handleOutgoingPacketThread.detach();
  }
}

void UDPClient::HandleIncomingPacket(sf::Packet &packet) {
  int operation;
  std::string site_id; // site id for the peer that created this operation
  int counter; // site counter of the peer that created this operation
  std::string text;
  int positions_size;
  std::vector<long> positions;
  std::string sender_site_id; // site id for the peer that sent this operation
  int sender_counter; // site counter for the peer that sent this operation.

  packet >> operation >> site_id >> counter >> text >> positions_size;

  for (int i = 0; i < positions_size; i++) {
    sf::Int64 position;
    packet >> position;
    positions.push_back((long) position);
  }
  packet >> sender_site_id >> sender_counter;
  CRDTAction crdt_action((CRDTOperation) operation, site_id, counter, text, positions);
  client_callbacks->OnRemoteOperationReceive(crdt_action, sender_site_id, sender_counter);
}

void UDPClient::ShutdownClient() {
  client_listening.store(false, std::memory_order_relaxed);
}

void UDPClient::SetClientCallbacks(NetworkingCallbacks *callbacks) {
  if (!callbacks) {
    throw CustomMessageException("NetworkingCallbacks cannot be set as null!");
  }
  this->client_callbacks = callbacks;
}
