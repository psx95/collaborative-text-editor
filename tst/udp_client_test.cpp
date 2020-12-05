//
// Created by psx95 on 11/28/20.
//
#include <catch.hpp>
#include <iostream>
#include "CommonStructs.hpp"
#include <../tst/mock_models/UDPClientMock.cpp>
TEST_CASE("Enter key - carriage return") {
  UPDClientMock udp_client_mock;
  std::vector<long> positions(1, 1);
  std::string site_id = "127.0.0.1:2002";
  int counter = 2;
  std::string text = "\r";
  CRDTAction action(INSERT, site_id, counter, text, positions);
  udp_client_mock.BroadcastActionToAllConnectedPeers(action);
  sf::Packet packet = udp_client_mock.GetPacket();
  udp_client_mock.HandleIncomingPacket(packet);
  REQUIRE(udp_client_mock.GetText() == text);
  REQUIRE(udp_client_mock.GetOperation() == INSERT);
  REQUIRE(udp_client_mock.GetSiteID() == site_id);
  REQUIRE(udp_client_mock.GetCounter() == counter);
  REQUIRE(udp_client_mock.GetPositions().size() == positions.size());
  for (int i = 0; i < action.Positions().size(); i++) {
    REQUIRE(udp_client_mock.GetPositions().at(i) == positions.at(i));
  }
}

TEST_CASE("letter - lower case") {
  UPDClientMock udp_client_mock;
  std::vector<long> positions(1, 1);
  std::string site_id = "127.0.0.1:2002";
  int counter = 2;
  std::string text = "w";
  CRDTAction action(DELETE, site_id, counter, text, positions);
  udp_client_mock.BroadcastActionToAllConnectedPeers(action);
  sf::Packet packet = udp_client_mock.GetPacket();
  udp_client_mock.HandleIncomingPacket(packet);
  REQUIRE(udp_client_mock.GetText() == text);
  REQUIRE(udp_client_mock.GetOperation() == DELETE);
  REQUIRE(udp_client_mock.GetSiteID() == site_id);
  REQUIRE(udp_client_mock.GetCounter() == counter);
  REQUIRE(udp_client_mock.GetPositions().size() == positions.size());
  for (int i = 0; i < action.Positions().size(); i++) {
    REQUIRE(udp_client_mock.GetPositions().at(i) == positions.at(i));
  }
}

TEST_CASE("letter - upper case") {
  UPDClientMock udp_client_mock;
  std::vector<long> positions(1, 1);
  std::string site_id = "127.0.0.1:2002";
  int counter = 2;
  std::string text = "A";
  CRDTAction action(INSERT, site_id, counter, text, positions);
  udp_client_mock.BroadcastActionToAllConnectedPeers(action);
  sf::Packet packet = udp_client_mock.GetPacket();
  udp_client_mock.HandleIncomingPacket(packet);
  REQUIRE(udp_client_mock.GetText() == text);
  REQUIRE(udp_client_mock.GetOperation() == INSERT);
  REQUIRE(udp_client_mock.GetSiteID() == site_id);
  REQUIRE(udp_client_mock.GetCounter() == counter);
  REQUIRE(udp_client_mock.GetPositions().size() == positions.size());
  for (int i = 0; i < action.Positions().size(); i++) {
    REQUIRE(udp_client_mock.GetPositions().at(i) == positions.at(i));
  }
}

TEST_CASE("Number") {
  UPDClientMock udp_client_mock;
  std::vector<long> positions(1, 1);
  std::string site_id = "127.0.0.1:2002";
  int counter = 2;
  std::string text = "3";
  CRDTAction action(INSERT, site_id, counter, text, positions);
  udp_client_mock.BroadcastActionToAllConnectedPeers(action);
  sf::Packet packet = udp_client_mock.GetPacket();
  udp_client_mock.HandleIncomingPacket(packet);
  REQUIRE(udp_client_mock.GetText() == text);
  REQUIRE(udp_client_mock.GetOperation() == INSERT);
  REQUIRE(udp_client_mock.GetSiteID() == site_id);
  REQUIRE(udp_client_mock.GetCounter() == counter);
  REQUIRE(udp_client_mock.GetPositions().size() == positions.size());
  for (int i = 0; i < action.Positions().size(); i++) {
    REQUIRE(udp_client_mock.GetPositions().at(i) == positions.at(i));
  }
}

TEST_CASE("Combination of keys") {
  UPDClientMock udp_client_mock;
  std::vector<long> positions(10, 1);
  std::string site_id = "127.0.0.1:2002";
  int counter = 2;
  std::string text = "sdkfhSADSsfndf31234jAWafhd4flA\r\r\n\nSADhD\r\n\tagj";
  CRDTAction action(DELETE, site_id, counter, text, positions);
  udp_client_mock.BroadcastActionToAllConnectedPeers(action);
  sf::Packet packet = udp_client_mock.GetPacket();
  udp_client_mock.HandleIncomingPacket(packet);
  REQUIRE(udp_client_mock.GetText() == text);
  REQUIRE(udp_client_mock.GetOperation() == DELETE);
  REQUIRE(udp_client_mock.GetSiteID() == site_id);
  REQUIRE(udp_client_mock.GetCounter() == counter);
  REQUIRE(udp_client_mock.GetPositions().size() == positions.size());
  for (int i = 0; i < action.Positions().size(); i++) {
    REQUIRE(udp_client_mock.GetPositions().at(i) == positions.at(i));
  }
}
