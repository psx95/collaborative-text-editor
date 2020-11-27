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

void UDPClient::BroadcastActionToAllConnectedPeers(CRDTAction &crdt_action) {

}

void UDPClient::HandleIncomingPacket(sf::Packet &packet) {
  //client_callbacks->OnRemoteOperationReceive(<packet parsed to get CRDTAction>);
}

void UDPClient::ShutdownClient() {

}

void UDPClient::SetClientCallbacks(NetworkingCallbacks *callbacks) {
  if (!callbacks) {
    throw CustomMessageException("NetworkingCallbacks cannot be set as null!");
  }
  this->client_callbacks = callbacks;
}
