//
// Created by psx95 on 12/2/20.
//

#include "iostream"
#include "algorithm"

#include "catch.hpp"

#include <CRDTManager.hpp>
#include "CustomMessageException.hpp"

CRDTManager *crdt_manager;

void Setup() {
  std::string site_id = "random_uuid_string";
  crdt_manager = new CRDTManager(site_id);
}

void SetupCRDTWithRandomCharactersInCRDT(int number_of_chars) {
  Setup();
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<int> random_number(97, 122);
  int site_counter = 0;
  for (int i = 0; i < number_of_chars; i++) {
    int random_char = random_number(gen);
    site_counter++;
    crdt_manager->GenerateCRDTActionForLocalInsert((char) random_char, i, site_counter);
  }
}

void PerformRandomInserts(int number_of_inserts) {
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<int> random_character_distribution(97, 122);
  std::uniform_int_distribution<int> random_index_distribution(0, crdt_manager->GetCRDTCharacters()->size() - 1);
  int site_counter = crdt_manager->GetCRDTCharacters()->at(crdt_manager->GetCRDTCharacters()->size() - 1).GetCounter();
  for (int i = 0; i < number_of_inserts; i++) {
    char random_char = random_character_distribution(gen);
    int random_index = random_index_distribution(gen);
    crdt_manager->GenerateCRDTActionForLocalInsert(random_char, random_index, site_counter++);
  }
}

void PerformRandomDeletes(int number_of_deletes) {
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<int> random_index_distribution(0, crdt_manager->GetCRDTCharacters()->size() - 1);
  int site_counter = crdt_manager->GetCRDTCharacters()->at(crdt_manager->GetCRDTCharacters()->size() - 1).GetCounter();
  if (!crdt_manager->GetCRDTCharacters()->empty()) {
    for (int i = 0; i < number_of_deletes; i++) {
      int random_index = std::min(random_index_distribution(gen), (int) crdt_manager->GetCRDTCharacters()->size() - 1);
      crdt_manager->GenerateCRDTActionForLocalDelete(random_index, site_counter++);
    }
  }
}

bool IsCharacterUniqueInCRDT(CRDTCharacter &crdt_character, int index) {
  for (int i = 0; i < crdt_manager->GetCRDTCharacters()->size(); i++) {
    if (i != index && crdt_character.ComparePositionTo(crdt_manager->GetCRDTCharacters()->at(i)) == 0) {
      std::cout << "Original Character position " << index << std::endl;
      for (const std::pair<long, std::string> &position :crdt_character.GetPositions()) {
        std::cout << position.first << ",";
      }
      std::cout << std::endl;
      std::cout << " Position " << i << std::endl;
      for (const std::pair<long, std::string> &position : crdt_manager->GetCRDTCharacters()->at(i).GetPositions()) {
        std::cout << position.first << ",";
      }
      std::cout << std::endl;
      return false;
    }
  }
  return true;
}

TEST_CASE("CRDT Insert increase CRDTCharacter struct size") {
  Setup();
  int last_index = crdt_manager->GetCRDTCharacters()->size();
  REQUIRE(last_index == 0);
  int current_site_counter = 0;
  crdt_manager->GenerateCRDTActionForLocalInsert('c', last_index, current_site_counter);
  REQUIRE(crdt_manager->GetCRDTCharacters()->size() == 1);
}

TEST_CASE("CRDT Delete on empty CRDT throws error") {
  Setup();
  int last_index = crdt_manager->GetCRDTCharacters()->size();
  REQUIRE(last_index == 0);
  int site_counter = 0;
  REQUIRE_THROWS(crdt_manager->GenerateCRDTActionForLocalDelete(last_index, site_counter));
}

TEST_CASE("CRDT Delete on invalid index throws error") {
  SetupCRDTWithRandomCharactersInCRDT(100);
  REQUIRE_THROWS(crdt_manager->GenerateCRDTActionForLocalDelete(100, 101));
}

TEST_CASE("CRDT Delete with valid index reduces number of characters") {
  SetupCRDTWithRandomCharactersInCRDT(100);
  REQUIRE(crdt_manager->GetCRDTCharacters()->size() == 100);
  REQUIRE_NOTHROW(crdt_manager->GenerateCRDTActionForLocalDelete(99, 100));
  REQUIRE(crdt_manager->GetCRDTCharacters()->size() == 99);
}

TEST_CASE("Load Test: Check Character Uniqueness") {
  SetupCRDTWithRandomCharactersInCRDT(10000);
  int total_fails = 0;
  for (int i = 0; i < crdt_manager->GetCRDTCharacters()->size(); i++) {
    CRDTCharacter crdt_character = crdt_manager->GetCRDTCharacters()->at(i);
    if (!IsCharacterUniqueInCRDT(crdt_character, i)) {
      total_fails++;
    }
  }
  std::cout << "Total uniqueness fails " << total_fails;
  REQUIRE(total_fails == 0);
}

TEST_CASE("Delete Test - Random deletes in a pre-filled CRDT removes characters") {
  SetupCRDTWithRandomCharactersInCRDT(2000);
  REQUIRE(crdt_manager->GetCRDTCharacters()->size() == 2000);
  PerformRandomDeletes(200);
  REQUIRE(crdt_manager->GetCRDTCharacters()->size() == 1800);
  PerformRandomDeletes(10);
  REQUIRE(crdt_manager->GetCRDTCharacters()->size() == 1790);
}

TEST_CASE("Insert Test - Random inserts in a pre-filled CRDT adds characters") {
  SetupCRDTWithRandomCharactersInCRDT(2000);
  REQUIRE(crdt_manager->GetCRDTCharacters()->size() == 2000);
  PerformRandomInserts(30);
  REQUIRE(crdt_manager->GetCRDTCharacters()->size() == 2030);
  for (int i = 0; i < crdt_manager->GetCRDTCharacters()->size(); i++) {
    CRDTCharacter crdt_character = crdt_manager->GetCRDTCharacters()->at(i);
    if (!IsCharacterUniqueInCRDT(crdt_character, i)) {
      FAIL();
    }
  }
  SUCCEED();
}