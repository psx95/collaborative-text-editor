//
// Created by psx95 on 11/28/20.
//
#include <catch.hpp>
#include <iostream>
#include "CommonStructs.hpp"
#include <../tst/mock_models/UDPClientMock.cpp>
TEST_CASE("Enter key - carriage return") {
  UPDClientMock udp_client_mock;
  std::vector<std::pair<long, std::string>> positions;
  positions.emplace_back(1, "s");
  positions.emplace_back(0, "s");
  std::string site_id = "127.0.0.1:2002";
  int counter = 2;
  std::string text = "\r";
  std::string sender_site_id = "127.0.0.1:2004";
  int sender_counter = 5;
  CRDTAction action(INSERT, site_id, counter, text, positions);
  udp_client_mock.BroadcastActionToAllConnectedPeers(action, sender_site_id, sender_counter);
  sf::Packet packet = udp_client_mock.GetPacket();
  udp_client_mock.HandleIncomingPacket(packet);
  REQUIRE(udp_client_mock.GetText() == text);
  REQUIRE(udp_client_mock.GetOperation() == INSERT);
  REQUIRE(udp_client_mock.GetSiteID() == site_id);
  REQUIRE(udp_client_mock.GetCounter() == counter);
  REQUIRE(action.Positions().size() == positions.size());
  for (int i = 0; i < action.Positions().size(); i++) {
    REQUIRE(action.Positions().at(i) == positions.at(i));
  }
  REQUIRE(udp_client_mock.GetSenderSiteID() == sender_site_id);
  REQUIRE(udp_client_mock.GetSenderCounter() == sender_counter);
}

TEST_CASE("letter - lower case") {
  UPDClientMock udp_client_mock;
  std::vector<std::pair<long, std::string>> positions;
  positions.emplace_back(1, "s");
  positions.emplace_back(0, "s");
  std::string site_id = "127.0.0.1:2002";
  int counter = 2;
  std::string text = "w";
  std::string sender_site_id = "127.0.0.1:2004";
  int sender_counter = 5;
  CRDTAction action(DELETE, site_id, counter, text, positions);
  udp_client_mock.BroadcastActionToAllConnectedPeers(action, sender_site_id, sender_counter);
  sf::Packet packet = udp_client_mock.GetPacket();
  udp_client_mock.HandleIncomingPacket(packet);
  REQUIRE(udp_client_mock.GetText() == text);
  REQUIRE(udp_client_mock.GetOperation() == DELETE);
  REQUIRE(udp_client_mock.GetSiteID() == site_id);
  REQUIRE(udp_client_mock.GetCounter() == counter);
  REQUIRE(action.Positions().size() == positions.size());
  for (int i = 0; i < action.Positions().size(); i++) {
    REQUIRE(action.Positions().at(i) == positions.at(i));
  }
  REQUIRE(udp_client_mock.GetSenderSiteID() == sender_site_id);
  REQUIRE(udp_client_mock.GetSenderCounter() == sender_counter);
}

TEST_CASE("letter - upper case") {
  UPDClientMock udp_client_mock;
  std::vector<std::pair<long, std::string>> positions;
  positions.emplace_back(1, "s");
  positions.emplace_back(0, "s");
  std::string site_id = "127.0.0.1:2002";
  int counter = 2;
  std::string text = "A";
  std::string sender_site_id = "127.0.0.1:2004";
  int sender_counter = 5;
  CRDTAction action(INSERT, site_id, counter, text, positions);
  udp_client_mock.BroadcastActionToAllConnectedPeers(action, sender_site_id, sender_counter);
  sf::Packet packet = udp_client_mock.GetPacket();
  udp_client_mock.HandleIncomingPacket(packet);
  REQUIRE(udp_client_mock.GetText() == text);
  REQUIRE(udp_client_mock.GetOperation() == INSERT);
  REQUIRE(udp_client_mock.GetSiteID() == site_id);
  REQUIRE(udp_client_mock.GetCounter() == counter);
  REQUIRE(action.Positions().size() == positions.size());
  for (int i = 0; i < action.Positions().size(); i++) {
    REQUIRE(action.Positions().at(i) == positions.at(i));
  }
  REQUIRE(udp_client_mock.GetSenderSiteID() == sender_site_id);
  REQUIRE(udp_client_mock.GetSenderCounter() == sender_counter);
}

TEST_CASE("Number") {
  UPDClientMock udp_client_mock;
  std::vector<std::pair<long, std::string>> positions;
  positions.emplace_back(1, "s");
  positions.emplace_back(0, "s");
  std::string site_id = "127.0.0.1:2002";
  int counter = 2;
  std::string text = "3";
  std::string sender_site_id = "127.0.0.1:2004";
  int sender_counter = 5;
  CRDTAction action(INSERT, site_id, counter, text, positions);
  udp_client_mock.BroadcastActionToAllConnectedPeers(action, sender_site_id, sender_counter);
  sf::Packet packet = udp_client_mock.GetPacket();
  udp_client_mock.HandleIncomingPacket(packet);
  REQUIRE(udp_client_mock.GetText() == text);
  REQUIRE(udp_client_mock.GetOperation() == INSERT);
  REQUIRE(udp_client_mock.GetSiteID() == site_id);
  REQUIRE(udp_client_mock.GetCounter() == counter);
  REQUIRE(action.Positions().size() == positions.size());
  for (int i = 0; i < action.Positions().size(); i++) {
    REQUIRE(action.Positions().at(i) == positions.at(i));
  }
  REQUIRE(udp_client_mock.GetSenderSiteID() == sender_site_id);
  REQUIRE(udp_client_mock.GetSenderCounter() == sender_counter);
}

TEST_CASE("Combination of keys") {
  UPDClientMock udp_client_mock;
  std::vector<std::pair<long, std::string>> positions;
  positions.emplace_back(1, "s");
  positions.emplace_back(0, "s");
  std::string site_id = "127.0.0.1:2002";
  int counter = 2;
  std::string text = "sdkfhSADSsfndf31234jAWafhd4flA\r\r\n\nSADhD\r\n\tagj";
  std::string sender_site_id = "127.0.0.1:2004";
  int sender_counter = 5;
  CRDTAction action(DELETE, site_id, counter, text, positions);
  udp_client_mock.BroadcastActionToAllConnectedPeers(action, sender_site_id, sender_counter);
  sf::Packet packet = udp_client_mock.GetPacket();
  udp_client_mock.HandleIncomingPacket(packet);
  REQUIRE(udp_client_mock.GetText() == text);
  REQUIRE(udp_client_mock.GetOperation() == DELETE);
  REQUIRE(udp_client_mock.GetSiteID() == site_id);
  REQUIRE(udp_client_mock.GetCounter() == counter);
  REQUIRE(action.Positions().size() == positions.size());
  for (int i = 0; i < action.Positions().size(); i++) {
    REQUIRE(action.Positions().at(i) == positions.at(i));
  }
  REQUIRE(udp_client_mock.GetSenderSiteID() == sender_site_id);
  REQUIRE(udp_client_mock.GetSenderCounter() == sender_counter);
}
