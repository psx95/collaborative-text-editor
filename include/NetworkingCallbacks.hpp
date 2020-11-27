//
// Created by psx95 on 11/27/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_NETWORKING_NETWORKINGCALLBACKS_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_NETWORKING_NETWORKINGCALLBACKS_HPP_

#include <SFML/Network/Packet.hpp>

/*!
 * @brief This class acts like interface callbacks for the UDPClient. This interface will allow implementing classes
 * to know of certain events that occur in the UDPClient.
 */
class NetworkingCallbacks {
 public:
  /*!
   * @brief This method notifies implementing classes about an insert event that occurs at another connected peer.
   * @details The implementation for this method should contain code that runs whenever a remote insert occurs.
   * @param packet The packet sent by the connected peer that contains details about an insert event.
   */
  virtual void OnRemoteInsertReceive(sf::Packet &packet);

  /*!
   * @brief This method notifies implementing classes about a delete event that occurs at another connected peer.
   * @details The implementation for this method should contain code that runs whenever a remote delete occurs.
   * @param packet The packet sent by the connected peer that contains details about a delete event.
   */
  virtual void OnRemoteDeleteReceive(sf::Packet &packet);
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_NETWORKING_NETWORKINGCALLBACKS_HPP_
