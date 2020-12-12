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
  std::vector<long> positions;

 public:

  UPDClientMock() {
  }

  void BroadcastActionToAllConnectedPeers(CRDTAction &crdt_action) {
    sf::Packet packet;
    packet << crdt_action.Operation() << crdt_action.SiteId() << crdt_action.Counter() << crdt_action.Text() <<
           (int) crdt_action.Positions().size();

    for (long position:crdt_action.Positions()) {
      packet << (sf::Int64) position;
    }
    this->packet = packet;
  }

  void HandleIncomingPacket(sf::Packet &packet) {
    int operation;
    std::string site_id;
    int counter;
    std::string received_text;
    int positions_size;
    std::vector<long> positions;

    packet >> operation >> site_id >> counter >> text >> positions_size;

    for (int i = 0; i < positions_size; i++) {
      sf::Int64 position;
      packet >> position;
      positions.push_back((long) position);
    }
    CRDTAction crdt_action((CRDTOperation) operation, site_id, counter, text, positions);

    this->text = text;
    this->operation = (CRDTOperation) operation;
    this->site_id = site_id;
    this->counter = counter;
    this->positions = positions;
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

  std::vector<long> GetPositions() {
    return this->positions;
  }

  sf::Packet GetPacket() {
    return this->packet;
  }

};
