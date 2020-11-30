//
// Created by psx95 on 11/27/20.
//

#include <cmath>
#include <random>

#include "CRDTManager.hpp"
#include <CustomMessageException.hpp>

CRDTManager::CRDTManager(std::string &site_id) : site_id(site_id) {
  this->strategy_map = new std::map<int, CRDTAllocationStrategy>();
  this->characters = new std::vector<struct CRDTCharacter>();
}

//================================================================================
// Public Methods
//================================================================================

struct CRDTAction CRDTManager::GenerateCRDTActionForLocalInsert(char c, int index, int site_counter) {
  CRDTCharacter character = GenerateCRDTCharacter(c, index, site_counter);
  this->characters->insert(this->characters->begin() + index, character);
  return CRDTAction(INSERT, character);
}

struct CRDTAction CRDTManager::GenerateCRDTActionForLocalDelete(int index, int site_counter) {
  CRDTCharacter character = this->characters->at(index);
  this->characters->erase(this->characters->begin() + index);
  return CRDTAction(DELETE, character);
}

std::pair<std::string, int> CRDTManager::GenerateStringInsertInfoFromRemoteInsert(CRDTAction &remote_action) {
  throw CustomMessageException("Not implemented yet!");
}

int CRDTManager::GenerateDeleteInfoFromRemoteDelete(CRDTAction &remote_action) {
  throw CustomMessageException("Not implemented yet!");
}


//================================================================================
// Private Helpers
//================================================================================

CRDTCharacter CRDTManager::GenerateCRDTCharacter(char c, int position_in_doc, int site_counter) {
  std::vector<int> position_before = GeneratePositionBefore(position_in_doc);
  std::vector<int> position_after = GeneratePositionAfter(position_in_doc);
  std::vector<int> new_position;
  GeneratePositionBetween(position_before, position_after, new_position);
  return CRDTCharacter(c, site_counter, this->site_id, new_position);
}

std::vector<int> CRDTManager::GeneratePositionBetween(std::vector<int> &before,
                                                      std::vector<int> &after,
                                                      std::vector<int> &generated_position,
                                                      int depth) {
  int base = (int) std::pow(base_multiple, depth) * this->starting_base;
  CRDTAllocationStrategy strategy_at_depth = GetAllocationStrategyForDepth(depth);
  // if no positions, then probably its a new level and in a new level, the available identifiers can go from 0 to
  // base size computed for that level (base size is exponentially increased at each level)
  int current_level_from_before_position = !before.empty() ? before.at(0) : 0;
  int current_level_from_after_position = !after.empty() ? after.at(0) : base;
  int interval_between_positions = current_level_from_after_position - current_level_from_before_position;
  if (interval_between_positions > 1) {
    // we have enough space to add a new character without increasing depth of the tree
    // generate a new position based on strategy
    int new_position = GenerateNewPositionIdentifier(current_level_from_before_position,
                                                     current_level_from_after_position,
                                                     strategy_at_depth);
    generated_position.push_back(new_position);
    return generated_position;
  } else if (interval_between_positions == 1) {
    // there is still not enough space and we need to add a new level to the tree
    generated_position.push_back(current_level_from_before_position);
    before.erase(before.begin());
    std::vector<int> vector;
    GeneratePositionBetween(before, vector, generated_position, depth + 1);
  } else if (interval_between_positions == 0) {
    // the start and end positions are the same, so have not yet reached the bottom of the tree (required depth) to make
    // decision about adding new level/inserting the character.
    generated_position.push_back(current_level_from_before_position);
    if (!before.empty()) {
      before.erase(before.begin());
    }
    if (!after.empty()) {
      after.erase(after.begin());
    }
    GeneratePositionBetween(before, after, generated_position, depth + 1);
  }
  return std::vector<int>();
}

std::vector<int> CRDTManager::GeneratePositionBefore(int index) {
  ThrowCustomExceptionOnNegativeIndex(index);
  if (index == 0) {
    return std::vector<int>();
  }
  return this->characters->at(index - 1).GetPositions();
}

std::vector<int> CRDTManager::GeneratePositionAfter(int index) {
  ThrowCustomExceptionOnNegativeIndex(index);
  if (index >= this->characters->size()) {
    return std::vector<int>();
  }
  return this->characters->at(index).GetPositions();
}

void CRDTManager::ThrowCustomExceptionOnNegativeIndex(int index) {
  if (index < 0) {
    throw CustomMessageException("Index cannot be negative! Check index!");
  }
}

CRDTAllocationStrategy CRDTManager::GetAllocationStrategyForDepth(int depth) {
  auto map_pos = strategy_map->find(depth);
  if (map_pos == strategy_map->end()) {
    strategy_map->insert(std::pair<int, CRDTAllocationStrategy>(depth, RANDOM));
    return RANDOM;
  }
  return map_pos->second;
}

int CRDTManager::GenerateNewPositionIdentifier(int minimum, int maximum, CRDTAllocationStrategy allocation_strategy) {
  // generate a random number between max & minimum, but within boundary
  int step_value = std::min(maximum - minimum, boundary);
  std::random_device rd;
  std::mt19937_64 gen(rd());
  if (allocation_strategy == RANDOM) {
    std::uniform_int_distribution<int> random_number(1, 2);
    allocation_strategy = static_cast<CRDTAllocationStrategy>(random_number(gen));
  }
  std::uniform_int_distribution<int> random_number(0, step_value);
  if (allocation_strategy == BOUNDARY_PLUS) {
    return minimum + 1 + random_number(gen);
  }
  if (allocation_strategy == BOUNDARY_MINUS) {
    return maximum - (1 + random_number(gen));
  }
  throw CustomMessageException("Fix Position Identifier Generation !");
}

//================================================================================
// Class Destructor
//================================================================================

CRDTManager::~CRDTManager() {
  if (!strategy_map->empty()) {
    strategy_map->clear();
  }
  if (!characters->empty()) {
    characters->clear();
  }
  delete strategy_map;
  delete characters;
}