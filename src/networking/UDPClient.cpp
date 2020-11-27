//
// Created by psx95 on 11/27/20.
//

#include <CustomMessageException.hpp>
#include "UDPClient.hpp"

UDPClient::UDPClient(unsigned short port, std::vector<struct PeerAddress> &peer_addresses) {
  this->client_port = port;
  this->peer_addresses = peer_addresses;
  Init();
}

void UDPClient::Init() {
  // Bind socket to port
  // Initialize socket
  StartListeningThread();
}

void UDPClient::StartListeningThread() {
  client_listening.store(true, std::memory_order_relaxed);
  // call handle packet from here
}

void UDPClient::BroadcastPacketToAllConnectedPeers(sf::Packet &packet) {

}

void UDPClient::HandleIncomingPacket(sf::Packet &packet) {
  // TODO: Based on Operation contained in packet, call either insert or delete.
  //client_callbacks->OnRemoteInsertReceive(packet);
  //client_callbacks->OnRemoteDeleteReceive(packet);
}

void UDPClient::ShutdownClient() {

}

void UDPClient::SetClientCallbacks(NetworkingCallbacks *callbacks) {
  if (!callbacks) {
    throw CustomMessageException("NetworkingCallbacks cannot be set as null!");
  }
  this->client_callbacks = callbacks;
}
