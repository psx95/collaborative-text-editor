#include <iostream>
#include <EditorWindow.hpp>
#include <ApplicationController.hpp>
#include <CRDTManager.hpp>
#include <VersionVector.hpp>
int main() {
  std::cout << "Starting Application" << std::endl;
  EditorWindow window(sf::Color(47, 50, 47));

  std::string unique_id("0");
  CRDTManager crdt_manager(unique_id);
  VersionVector version_vector;
  std::vector<struct PeerAddress> dummy_peers; // take from console
  UDPClient udp_client(2000, dummy_peers);

  ApplicationController controller(window, crdt_manager, udp_client, version_vector);
  controller.Go();
  controller.Shutdown();
  
  return 0;
}
