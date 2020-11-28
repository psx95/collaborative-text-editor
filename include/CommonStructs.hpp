//
// Created by psx95 on 11/27/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_INCLUDE_COMMONSTRUCTS_HPP_
#define COLLABORATIVE_TEXT_EDITOR_INCLUDE_COMMONSTRUCTS_HPP_

#include <string>
#include <SFML/Network/IpAddress.hpp>

enum CRDTOperation {
  INSERT = 0,
  DELETE = 1
};

struct CRDTAction {
  CRDTOperation operation;
  int site_id; // unique id of the client
  int counter; // site counter managed by version vector
  std::string text; // value of the string (current support for single chars) to be inserted.
  int positions[]; // fractional position calculated by CRDT.
};

struct PeerAddress {
  sf::IpAddress ip_address; // ensures that the address is complaint & valid, not just any random string
  unsigned short port{}; // port at which the connected client runs.
};

#endif //COLLABORATIVE_TEXT_EDITOR_INCLUDE_COMMONSTRUCTS_HPP_
