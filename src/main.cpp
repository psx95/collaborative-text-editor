#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <EditorWindow.hpp>
#include <ApplicationController.hpp>
#include <CRDTManager.hpp>
#include <VersionVector.hpp>
#include <stdlib.h>
std::string generateUniqueId();

int main(int argc, char** argv) {
  std::cout << "Starting Application" << std::endl;

  if(argc < 3 || argc!=(3 + 2 * atoi(argv[2]))){
  std::cout<<"Error: Not enough or invalid arguments, please enter in this format ./editor <client_port> <no_of_peers>"
             " [<peer_ip> <peer_port> ...]"<<std::endl;
  return 1;
  }
  std::vector<PeerAddress> peers; // take from console
  for(int i=3;i<argc;i=i+2){
    peers.push_back({sf::IpAddress(argv[i]),(unsigned short)(atoi(argv[i+1]))});
  }


  EditorWindow window(sf::Color(47, 50, 47));

  std::string unique_id = generateUniqueId();
  CRDTManager crdt_manager(unique_id);
  VersionVector version_vector;

  std::vector<struct PeerAddress> dummy_peers; // take from console
  UDPClient udp_client(atoi(argv[1]), peers);


  std::vector<int> positions(5, 1);
  std::string site_id = "127.0.0.1:2002";
  int counter = 2;
  std::string text = "w";
  CRDTAction crdt_action(DELETE, site_id, counter, text, positions);

  udp_client.BroadcastActionToAllConnectedPeers(crdt_action);
  ApplicationController controller(window, crdt_manager, udp_client, version_vector);
  controller.Go();
  controller.Shutdown();
  udp_client.ShutdownClient();
  return 0;
}

std::string generateUniqueId() {
  boost::uuids::random_generator generator;
  boost::uuids::uuid uuid = generator();

  return boost::uuids::to_string(uuid);
}
