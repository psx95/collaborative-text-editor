//
// Created by psx95 on 11/28/20.
//
#define CATCH_CONFIG_MAIN // need only be in one of the test files
#include <catch.hpp>
#include "CommonStructs.hpp"

TEST_CASE("Initializing CRDTAction immutable") {
  std::vector<int> positions(1, 0);
  std::string site_id = "127.0.0.1:2002";
  int counter = 2;
  std::string text = "w";
  CRDTAction action(INSERT, site_id, counter, text, positions);
  REQUIRE(action.Operation() == INSERT);
  REQUIRE(action.SiteId() == site_id);
  REQUIRE(action.Counter() == counter);
  REQUIRE(action.Text() == text);
  REQUIRE(action.Positions().size() == positions.size());
  for (int i = 0; i < action.Positions().size(); i++) {
    REQUIRE(action.Positions().at(i) == positions.at(i));
  }
}

TEST_CASE("Immutable CRDTAction maybe replaced") {
  std::vector<int> positions(1, 0);
  std::string site_id = "127.0.0.1:2002";
  int counter = 2;
  std::string text = "w";
  CRDTAction action(INSERT, site_id, counter, text, positions);
  REQUIRE(action.Operation() == INSERT);
  REQUIRE(action.SiteId() == site_id);
  REQUIRE(action.Counter() == counter);
  REQUIRE(action.Text() == text);
  REQUIRE(action.Positions().size() == positions.size());
  for (int i = 0; i < action.Positions().size(); i++) {
    REQUIRE(action.Positions().at(i) == positions.at(i));
  }

  std::vector<int> positions_1(1, 2);
  std::string site_id_1 = "127.0.0.1:2003";
  int counter_1 = 3;
  std::string text_1 = "q";
  CRDTAction action1(INSERT, site_id_1, counter_1, text_1, positions_1);
  action = action1; // replace entire struct
  REQUIRE(action.Operation() == INSERT);
  REQUIRE(action.SiteId() == site_id_1);
  REQUIRE(action.Counter() == counter_1);
  REQUIRE(action.Text() == text_1);
  REQUIRE(action.Positions().size() == positions_1.size());
  for (int i = 0; i < action.Positions().size(); i++) {
    REQUIRE(action.Positions().at(i) == positions_1.at(i));
  }
}
