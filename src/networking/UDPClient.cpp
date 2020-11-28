//
// Created by psx95 on 11/27/20.
//

#include <CustomMessageException.hpp>
#include "UDPClient.hpp"
#include<iostream>


UDPClient::UDPClient(unsigned short port, std::vector<struct PeerAddress> &peer_addresses) {
  this->client_port = port;
  this->peer_addresses = peer_addresses;
  for(PeerAddress peer: peer_addresses){
    std::cout<<peer.ip_address<<"\t"<<peer.port<<std::endl;
  }
  Init();
}

void UDPClient::Init() {
  // Bind socket to port
 client_socket.bind(this->client_port);
  // Initialize socket
  std::thread ListeningThread(&UDPClient::StartListeningThread, this);
  //ListeningThread.detach(); - need to try this
  thread_vector.push_back(std::move(ListeningThread));
  std::cout<<"Thread ended "<<std::endl;
}

void UDPClient::StartListeningThread() {
  std::cout<<"Listening "<<std::endl;
  client_listening.store(true, std::memory_order_relaxed);
  while(client_listening.load(std::memory_order_relaxed)){
    char buffer[1024];
    std::size_t received = 0;
    sf::IpAddress sender;
    unsigned short port;
    client_socket.receive(buffer, sizeof(buffer), received, sender, port);
    std::cout << sender.toString() << " said: " << buffer << std::endl;
  }
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
