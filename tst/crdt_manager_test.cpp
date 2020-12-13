//
// Created by psx95 on 12/2/20.
//

#include "iostream"
#include "algorithm"

#include "catch.hpp"

#include <CRDTManager.hpp>
#include "CustomMessageException.hpp"

namespace test_helpers {

CRDTManager SetupCRDTWithRandomCharactersInCRDT(int number_of_chars, std::string &site_id) {
  CRDTManager crdt_manager = CRDTManager(site_id);
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<int> random_number(97, 122);
  int site_counter = 0;
  for (int i = 0; i < number_of_chars; i++) {
    int random_char = random_number(gen);
    site_counter++;
    crdt_manager.GenerateCRDTActionForLocalInsert((char) random_char, i, site_counter);
  }
  return crdt_manager;
}

void PerformRandomInserts(int number_of_inserts, CRDTManager &crdt_manager) {
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<int> random_character_distribution(97, 122);
  std::uniform_int_distribution<int> random_index_distribution(0, crdt_manager.GetCRDTCharacters()->size() - 1);
  int site_counter = crdt_manager.GetCRDTCharacters()->at(crdt_manager.GetCRDTCharacters()->size() - 1).GetCounter();
  for (int i = 0; i < number_of_inserts; i++) {
    char random_char = random_character_distribution(gen);
    int random_index = random_index_distribution(gen);
    crdt_manager.GenerateCRDTActionForLocalInsert(random_char, random_index, site_counter++);
  }
}

void PerformRandomDeletes(int number_of_deletes, CRDTManager &crdt_manager) {
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<int> random_index_distribution(0, crdt_manager.GetCRDTCharacters()->size() - 1);
  int site_counter = crdt_manager.GetCRDTCharacters()->at(crdt_manager.GetCRDTCharacters()->size() - 1).GetCounter();
  if (!crdt_manager.GetCRDTCharacters()->empty()) {
    for (int i = 0; i < number_of_deletes; i++) {
      int random_index = std::min(random_index_distribution(gen), (int) crdt_manager.GetCRDTCharacters()->size() - 1);
      crdt_manager.GenerateCRDTActionForLocalDelete(random_index, site_counter++);
    }
  }
}

bool IsCharacterUniqueInCRDT(CRDTCharacter &crdt_character, int index, CRDTManager &crdt_manager) {
  for (int i = 0; i < crdt_manager.GetCRDTCharacters()->size(); i++) {
    if (i != index && crdt_character.ComparePositionTo(crdt_manager.GetCRDTCharacters()->at(i)) == 0) {
      std::cout << "Original Character position " << index << std::endl;
      for (const std::pair<long, std::string> &position :crdt_character.GetPositions()) {
        std::cout << position.first << ",";
      }
      std::cout << std::endl;
      std::cout << " Position " << i << std::endl;
      for (const std::pair<long, std::string> &position : crdt_manager.GetCRDTCharacters()->at(i).GetPositions()) {
        std::cout << position.first << ",";
      }
      std::cout << std::endl;
      return false;
    }
  }
  return true;
}
}

TEST_CASE("CRDT Insert increase CRDTCharacter struct array size") {
  std::string site_id = "site_id";
  CRDTManager crdt_manager(site_id);
  int last_index = crdt_manager.GetCRDTCharacters()->size();
  REQUIRE(last_index == 0);
  int site_counter = 0;
  CRDTAction action = crdt_manager.GenerateCRDTActionForLocalInsert('c', 0, site_counter);
  REQUIRE(crdt_manager.GetCRDTCharacters()->size() == 1);
}

TEST_CASE("CRDT Delete on empty CRDT throws error") {
  std::string site_id = "site_id";
  CRDTManager crdt_manager(site_id);
  int last_index = crdt_manager.GetCRDTCharacters()->size();
  REQUIRE(last_index == 0);
  int site_counter = 0;
  REQUIRE_THROWS(crdt_manager.GenerateCRDTActionForLocalDelete(last_index, site_counter));
}

TEST_CASE("CRDT Delete on invalid index throws error") {
  std::string site_id = "site_id";
  CRDTManager crdt_manager = test_helpers::SetupCRDTWithRandomCharactersInCRDT(100, site_id);
  REQUIRE_THROWS(crdt_manager.GenerateCRDTActionForLocalDelete(100, 101));
}

TEST_CASE("CRDT Delete with valid index reduces number of characters") {
  std::string site_id = "site_id";
  CRDTManager crdt_manager = test_helpers::SetupCRDTWithRandomCharactersInCRDT(100, site_id);
  REQUIRE(crdt_manager.GetCRDTCharacters()->size() == 100);
  REQUIRE_NOTHROW(crdt_manager.GenerateCRDTActionForLocalDelete(99, 100));
  REQUIRE(crdt_manager.GetCRDTCharacters()->size() == 99);
}

TEST_CASE("Load Test: Check Character Uniqueness") {
  std::string site_id = "site_id";
  CRDTManager crdt_manager = test_helpers::SetupCRDTWithRandomCharactersInCRDT(8000, site_id);
  int total_fails = 0;
  for (int i = 0; i < crdt_manager.GetCRDTCharacters()->size(); i++) {
    CRDTCharacter crdt_character = crdt_manager.GetCRDTCharacters()->at(i);
    if (!test_helpers::IsCharacterUniqueInCRDT(crdt_character, i, crdt_manager)) {
      total_fails++;
    }
  }
  std::cout << "Total uniqueness fails " << total_fails;
  REQUIRE(total_fails == 0);
}

TEST_CASE("Delete Test - Random deletes in a pre-filled CRDT removes characters") {
  std::string site_id = "site_id";
  CRDTManager crdt_manager = test_helpers::SetupCRDTWithRandomCharactersInCRDT(2000, site_id);
  REQUIRE(crdt_manager.GetCRDTCharacters()->size() == 2000);
  test_helpers::PerformRandomDeletes(200, crdt_manager);
  REQUIRE(crdt_manager.GetCRDTCharacters()->size() == 1800);
  test_helpers::PerformRandomDeletes(10, crdt_manager);
  REQUIRE(crdt_manager.GetCRDTCharacters()->size() == 1790);
}

TEST_CASE("Insert Test - Random inserts in a pre-filled CRDT adds characters") {
  std::string site_id = "site_id";
  CRDTManager crdt_manager = test_helpers::SetupCRDTWithRandomCharactersInCRDT(2000, site_id);
  REQUIRE(crdt_manager.GetCRDTCharacters()->size() == 2000);
  test_helpers::PerformRandomInserts(30, crdt_manager);
  REQUIRE(crdt_manager.GetCRDTCharacters()->size() == 2030);
  for (int i = 0; i < crdt_manager.GetCRDTCharacters()->size(); i++) {
    CRDTCharacter crdt_character = crdt_manager.GetCRDTCharacters()->at(i);
    if (!test_helpers::IsCharacterUniqueInCRDT(crdt_character, i, crdt_manager)) {
      FAIL();
    }
  }
  SUCCEED();
}
