//
// Created by sharan on 12/4/20.
//

#include <vector>
#include <SFML/Network/Packet.hpp>
#include "CustomMessageException.hpp"
#include "CommonStructs.hpp"

/* This class represents the mock fo the UDPClient class and is mainly responsible for testing the outputs of
UDPClient's functions */
class UPDClientMock {

 private:
  std::string text;
  sf::Packet packet;
  CRDTOperation operation;
  std::string site_id;
  int counter;
  std::vector<std::pair<long, std::string>> positions;
  std::string sender_site_id;
  int sender_counter;

 public:

  UPDClientMock() {
  }

  void BroadcastActionToAllConnectedPeers(CRDTAction &crdt_action, std::string &site_id, int site_counter) {
    sf::Packet packet;
    packet << crdt_action.Operation() << crdt_action.SiteId() << crdt_action.Counter() << crdt_action.Text() <<
           (int) crdt_action.Positions().size();

    for (const std::pair<long, std::string> &position:crdt_action.Positions()) {
      packet << (sf::Int64) position.first << position.second;
    }
    packet << site_id << site_counter;
    this->packet = packet;
  }

  void HandleIncomingPacket(sf::Packet &packet) {
    int operation;
    std::string site_id; // site id for the peer that created this operation
    int counter; // site counter of the peer that created this operation
    std::string text;
    int positions_size;
    std::vector<std::pair<long, std::string>> positions;
    std::string sender_site_id; // site id for the peer that sent this operation
    int sender_counter; // site counter for the peer that sent this operation.

    packet >> operation >> site_id >> counter >> text >> positions_size;

    for (int i = 0; i < positions_size; i++) {
      sf::Int64 position;
      std::string position_site_id;
      packet >> position >> position_site_id;
      positions.emplace_back((long) position, position_site_id);
    }
    packet >> sender_site_id >> sender_counter;
    CRDTAction crdt_action((CRDTOperation) operation, site_id, counter, text, positions);

    this->text = text;
    this->operation = (CRDTOperation) operation;
    this->site_id = site_id;
    this->counter = counter;
    this->positions = positions;
    this->sender_site_id = sender_site_id;
    this->sender_counter = sender_counter;
  }

  std::string GetText() {
    return this->text;
  }

  CRDTOperation GetOperation() {
    return this->operation;
  }

  std::string GetSiteID() {
    return this->site_id;
  }

  int GetCounter() {
    return this->counter;
  }

  std::vector<std::pair<long, std::string>> GetPositions() {
    return this->positions;
  }

  sf::Packet GetPacket() {
    return this->packet;
  }

  std::string GetSenderSiteID() {
    return this->sender_site_id;
  }

  int GetSenderCounter() {
    return this->sender_counter;
  }

};
