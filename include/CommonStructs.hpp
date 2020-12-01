//
// Created by psx95 on 11/27/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_INCLUDE_COMMONSTRUCTS_HPP_
#define COLLABORATIVE_TEXT_EDITOR_INCLUDE_COMMONSTRUCTS_HPP_

#include <string>
#include <vector>
#include <SFML/Network/IpAddress.hpp>
#include<iostream>

enum CRDTOperation {
  INSERT = 0,
  DELETE = 1
};

/*!
 * @brief This struct represents a basic CRDTAction. Its the basic unit that is used by CRDTManager to uniquely identify
 * individual characters shared across multiple peers.
 * @details The struct is immutable and therefore can be passed freely with a guarantee that the contents(state) of the
 * struct will not be modified. However, they can still be completely replaced by assigning a completely new value to
 * struct.
 */
struct CRDTAction {
 public:
  CRDTAction(CRDTOperation operation,
             std::string &site_id,
             int counter,
             std::string &text,
             std::vector<long> &positions)
      : operation(operation), site_id(site_id), counter(counter), text(text), positions(positions) {
  }

  CRDTOperation Operation() const {
    return operation;
  }

  std::string SiteId() const {
    return site_id;
  }

  int Counter() const {
    return counter;
  }

  std::string Text() const {
    return text;
  }

  std::vector<long> Positions() const {
    return positions;
  }

  std::string toString() {
    std::string crdt_action_str;
    crdt_action_str.append("Operation").append("\t").append(std::to_string(operation)).append("\n")
        .append("site_id").append("\t").append(site_id).append("\n")
        .append("counter").append("\t").append(std::to_string(counter)).append("\n")
        .append("text").append("\t").append(text).append("\n")
        .append("positions").append("\t");
    for (long position:positions) {
      crdt_action_str.append(std::to_string(position)).append("\t");
    }
    return crdt_action_str.append("\n");
  }

 private:
  CRDTOperation operation;
  std::string site_id; // unique id of the client
  int counter; // site counter managed by version vector
  std::string text; // value of the string (current support for single chars) to be inserted.
  std::vector<long> positions; // fractional position calculated by CRDT.
};

struct PeerAddress {
  sf::IpAddress ip_address; // ensures that the address is complaint & valid, not just any random string
  unsigned short port; // port at which the connected client runs.
};

#endif //COLLABORATIVE_TEXT_EDITOR_INCLUDE_COMMONSTRUCTS_HPP_
