#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <EditorWindow.hpp>
#include <ApplicationController.hpp>
#include <CRDTManager.hpp>
#include <VersionVector.hpp>

std::string generateUniqueId();

int main() {
  std::cout << "Starting Application" << std::endl;
  EditorWindow window(sf::Color(47, 50, 47));

  std::string unique_id = generateUniqueId();
  CRDTManager crdt_manager(unique_id);
  VersionVector version_vector;

  std::vector<struct PeerAddress> dummy_peers; // take from console
  UDPClient udp_client(2000, dummy_peers);

  ApplicationController controller(window, crdt_manager, udp_client, version_vector);
  controller.Go();
  controller.Shutdown();

  return 0;
}

std::string generateUniqueId() {
  boost::uuids::random_generator generator;
  boost::uuids::uuid uuid = generator();

  return boost::uuids::to_string(uuid);
}
