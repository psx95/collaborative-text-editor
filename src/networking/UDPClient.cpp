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
}

CRDTOperation operation;
std::string site_id; // unique id of the client
int counter; // site counter managed by version vector
std::string text; // value of the string (current support for single chars) to be inserted.

void UDPClient::StartListeningThread() {
  client_listening.store(true, std::memory_order_relaxed);
  while(client_listening.load(std::memory_order_relaxed)){
    std::cout<<"Listening "<<std::endl;
    sf::Packet packet;
    sf::IpAddress sender;
    unsigned short port;
    client_socket.receive(packet, sender,port);
    int operation;
    std::string site_id; // unique id of the client
    int counter; // site counter managed by version vector
    std::string text; // value of the string (current support for single chars) to be inserted.
    int positions_size;
    std::vector<int> positions; // fractional position calculated by CRDT.

    packet >>operation >> site_id >> counter >> text >>positions_size;

    for(int i=0;i<positions_size;i++){
      int position;
      packet>>position;
      positions.push_back(position);
    }
    CRDTAction crdt_action((CRDTOperation) operation, site_id, counter, text, positions);
    crdt_action.Print();
  }
}



void UDPClient::BroadcastActionToAllConnectedPeers(CRDTAction &crdt_action) {
  //packet << crdt_action.site_id << crdt_action.counter << crdt_action.text;
  for(PeerAddress peer_address: this->peer_addresses){
    sf::Packet packet;
    packet << crdt_action.Operation() << crdt_action.SiteId() << crdt_action.Counter() << crdt_action.Text() <<
    (int)crdt_action.Positions().size();

    for(int position:crdt_action.Positions()){
      packet<<position;
    }
    std::cout<<"Broadcast - "<<peer_address.ip_address<<"\t"<<"port"<<peer_address.port<<std::endl;
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
