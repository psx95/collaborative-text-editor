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

CRDTOperation operation;
std::string site_id; // unique id of the client
int counter; // site counter managed by version vector
std::string text; // value of the string (current support for single chars) to be inserted.

sf::Packet& operator <<(sf::Packet& packet, const CRDTAction& crdt_action)
{
  return packet << crdt_action.site_id << crdt_action.counter << crdt_action.text;
}

sf::Packet& operator >>(sf::Packet& packet, CRDTAction& crdt_action)
{
  return packet  >> crdt_action.site_id >> crdt_action.counter >> crdt_action.text;
}


void UDPClient::StartListeningThread() {
  std::cout<<"Listening "<<std::endl;
  client_listening.store(true, std::memory_order_relaxed);
  CRDTAction crdt_action;
  while(client_listening.load(std::memory_order_relaxed)){
    std::cout<<"Listening True"<<std::endl;

    sf::Packet packet;
    sf::IpAddress sender;
    unsigned short port;
    //client_socket.receive(&packet, sizeof(buffer), received, sender, port);
    client_socket.receive(packet, sender,port);
    packet>>crdt_action;
//    if (packet >> crdt_action.site_id >> crdt_action.counter >> crdt_action.text)
//    {
//      std::cout<<"Data extracted successfully "<<std::endl;
//    }
//    else{
//      std::cout<<"Failed! - Data extraction"<<std::endl;
//    }
    std::cout<<"Output "<<"crdt_action.site_id "<< crdt_action.site_id<<"\t"<<"crdt_action.counter "<<crdt_action.counter<<"crdt_action.text "<<crdt_action.text<<std::endl;
  }
}



void UDPClient::BroadcastActionToAllConnectedPeers(CRDTAction &crdt_action) {
  sf::Packet packet;
  //packet << crdt_action.site_id << crdt_action.counter << crdt_action.text;
  packet<<crdt_action;

  for(PeerAddress peer_address: this->peer_addresses){
    std::cout<<"Sending it to IP address "<<peer_address.ip_address<<"port "<<peer_address.port<<std::endl;
    client_socket.send(packet,peer_address.ip_address,peer_address.port);
  }

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
