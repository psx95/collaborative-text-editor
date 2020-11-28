#include <iostream>
#include <EditorWindow.hpp>
#include <ApplicationController.hpp>
#include <CRDTManager.hpp>
#include <VersionVector.hpp>
int main() {
  std::cout << "Starting Application" << std::endl;
  EditorWindow window(sf::Color(47, 50, 47));

  CRDTManager crdt_manager(0);
  VersionVector version_vector;
  std::vector<struct PeerAddress> dummy_peers; // take from console
  UDPClient udp_client(2000, dummy_peers);

  ApplicationController controller(window, crdt_manager, udp_client, version_vector);
  controller.Go();
  controller.Shutdown();
  return 0;
}
