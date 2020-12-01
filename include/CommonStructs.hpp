//
// Created by psx95 on 11/27/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_INCLUDE_COMMONSTRUCTS_HPP_
#define COLLABORATIVE_TEXT_EDITOR_INCLUDE_COMMONSTRUCTS_HPP_

#include <string>
#include <vector>
#include <SFML/Network/IpAddress.hpp>
#include <iostream>

#include "CRDTCharacter.hpp"

enum CRDTOperation {
  INSERT = 0,
  DELETE = 1
};

/*!
 * @brief This enum holds the allocation strategies that can be used to generate a new value to add to the positions
 * array for a CRDTCharacter.
 */
enum CRDTAllocationStrategy {

  /*!
   * @brief Randomly choose between BOUNDARY_PLUS and BOUNDARY_MINUS.
   */
  RANDOM = 0,

  /*!
   * @brief This strategy will generate a random number between a range that is closer to the beginning of the range.
   * @details This strategy is more suitable for edits at the end of the document.
   */
  BOUNDARY_PLUS = 1,

  /*!
   * @brief This strategy will generate a random number between a range that is closer to the end of the range.
   * @details This strategy is more suitable for edits made at the beginning of the document.
   */
  BOUNDARY_MINUS = 2
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
             std::string &site_id, // site_id of the client that is responsible for originally creating the operation.
             int counter, // site counter of the client that is responsible for originally creating the operation.
             std::string &text,
             std::vector<long> &positions)
      : operation(operation), site_id(site_id), counter(counter), text(text), positions(positions) {
  }

  /*!
   * @brief Public constructor for CRDTAction.
   * @details This is a simplified constructor that gives an overall picture of the CRDTAction.
   * @param operation The operation that needs to be performed with the character.
   * @param character The CRDTCharacter on which the operation needs to be performed.
   */
  CRDTAction(CRDTOperation operation, CRDTCharacter &character) : operation(operation) {
    site_id = character.GetSiteId();
    counter = character.GetCounter();
    text = character.GetValue();
    positions = character.GetPositions();
  }

  /*!
   * @brief Calling this method will generate a CRDTCharacter from the raw values contained in the struct.
   * @return A copy of CRDTCharacter object on which this CRDTAction was intended.
   */
  CRDTCharacter Character() {
    return CRDTCharacter(text.at(0), counter, site_id, positions);
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

  std::string ToString() {
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

  // overriding < operator for std::set
  bool operator<(const CRDTAction &msgObj) const {
    return (this->counter < msgObj.counter);
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
