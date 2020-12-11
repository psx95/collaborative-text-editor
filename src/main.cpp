#include <iostream>
#include <cstdlib>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <EditorWindow.hpp>
#include <ApplicationController.hpp>
#include <CRDTManager.hpp>
#include <VersionVector.hpp>
#include <CustomMessageException.hpp>
std::string generateUniqueId();

int main(int argc, char **argv) {
  if (argc < 3 || argc != (3 + 2 * strtoul(argv[2], nullptr, 10))) {
    std::cerr
        << "Error: Not enough or invalid arguments, please enter in this format ./collaborative_text_editor "
        << "<client_port> <no_of_peers> [<peer_ip> <peer_port> ...]"
        << std::endl;
    return -1;
  }
  std::vector<PeerAddress> peers; // take from console
  for (int i = 3; i < argc; i = i + 2) {
    peers.push_back({sf::IpAddress(argv[i]), (unsigned short) (strtoul(argv[i + 1], nullptr, 10))});
  }

  std::string unique_id = generateUniqueId();
  EditorWindow window(sf::Color(47, 50, 47), unique_id);
  CRDTManager crdt_manager(unique_id);
  VersionVector version_vector(unique_id);
  unsigned int port = strtoul(argv[1], nullptr, 10);
  UDPClient udp_client(port, peers);

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
