//
// Created by psx95 on 11/27/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_NETWORKING_UDPCLIENT_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_NETWORKING_UDPCLIENT_HPP_

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/Network/UdpSocket.hpp>
#include <vector>
#include <atomic>
#include "CommonStructs.hpp"
#include "NetworkingCallbacks.hpp"
#include <thread>

class UDPClient {
 private:
  unsigned short client_port; // port at which the current client is running
  std::vector<struct PeerAddress> peer_addresses; // a list of all connected peers
  std::atomic<bool> client_listening{}; // a boolean to indicate if the current client is listening for incoming packets
  NetworkingCallbacks *client_callbacks{}; // client callbacks used by controller to define code that must run on events
  sf::UdpSocket client_socket; // the udp socket which the client app can use for networking
  std::vector<std::thread> thread_vector;
  void Init(); // any one time initialization steps
  void StartListeningThread(); // helper method to start the listening functionality in a background thread
  void HandleIncomingPacket(sf::Packet &packet); // handle incoming packet with CRDT Action
  void HandleOutgoingPacket(sf::Packet packet, PeerAddress peer_address); // handle incoming packet with CRDT Action

 public:
  /*!
   * @brief Public constructor for UDPClient.
   * @param port The port to which the current client should bind to.
   * @param peer_addresses A list of peer addresses to which the client will broadcast packets.
   */
  explicit UDPClient(unsigned short port, std::vector<struct PeerAddress> &peer_addresses);

  /*!
   * @brief This method will broadcast a single packet (should contain a single Operation) to all connected clients.
   * @param crdt_action The CRDTAction that needs to be reflected on all connected peers.
   */
  void BroadcastActionToAllConnectedPeers(struct CRDTAction &crdt_action);

  /*!
   * @brief This method sets the NetworkingCallbacks for the UpdClient.
   * @param client_callbacks The callbacks that can be used to define code that runs on certain networking events.
   * @throws CustomMessageException if the passed client_callbacks is null.
   */
  void SetClientCallbacks(NetworkingCallbacks *client_callbacks);

  /*!
   * @brief This method should be called before exiting or when the client explicitly wants to disconnect from network.
   * @details This method contains code that guarantees safe disconnect and stops any background threads running in the
   * system.
   */
  void ShutdownClient(); // safe disconnect + stop listening thread

};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_NETWORKING_UDPCLIENT_HPP_
