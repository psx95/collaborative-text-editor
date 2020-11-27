#include <iostream>
#include <EditorWindow.hpp>
#include <ApplicationController.hpp>
#include <CRDTManager.hpp>

int main() {
  std::cout << "Starting Application" << std::endl;
  EditorWindow window(sf::Color(47, 50, 47));
  CRDTManager crdt_manager(0);
  std::vector<struct PeerAddress> dummy_peers; // take from console
  UDPClient udp_client(2000, dummy_peers);
  ApplicationController controller(window, crdt_manager, udp_client);
  controller.Go();
  controller.Shutdown();
  return 0;
}
