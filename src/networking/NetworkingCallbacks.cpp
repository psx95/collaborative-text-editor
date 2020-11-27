//
// Created by psx95 on 11/27/20.
//

#include <CustomMessageException.hpp>
#include "NetworkingCallbacks.hpp"

void NetworkingCallbacks::OnRemoteInsertReceive(sf::Packet &packet) {
  throw CustomMessageException("OnRemoteInsertReceive not implemented yet!");
}

void NetworkingCallbacks::OnRemoteDeleteReceive(sf::Packet &packet) {
  throw CustomMessageException("OnRemoteDeleteReceive not implemented yet!");
}
