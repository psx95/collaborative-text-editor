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
  int remote_insert_position = (int) this->FindRemoteInsertPosition(remote_action.Character());
  this->characters->insert(this->characters->begin() + remote_insert_position, remote_action.Character());
  return {remote_action.Text(), remote_insert_position};
}

int CRDTManager::GenerateDeleteInfoFromRemoteDelete(CRDTAction &remote_action) {
  int remote_delete_position = (int) this->FindRemoteDeletePosition(remote_action.Character());
  this->characters->erase(this->characters->begin() + remote_delete_position);
  return remote_delete_position;
}

std::vector<CRDTCharacter> *CRDTManager::GetCRDTCharacters() const {
  return this->characters;
}

//================================================================================
// Private Helpers
//================================================================================

CRDTCharacter CRDTManager::GenerateCRDTCharacter(char c, int position_in_doc, int site_counter) {
  std::vector<long> position_before = GeneratePositionBefore(position_in_doc);
  std::vector<long> position_after = GeneratePositionAfter(position_in_doc);
  std::vector<long> new_position;
  GeneratePositionBetween(position_before, position_after, new_position);
  return CRDTCharacter(c, site_counter, this->site_id, new_position);
}

std::vector<long> CRDTManager::GeneratePositionBetween(std::vector<long> &before,
                                                       std::vector<long> &after,
                                                       std::vector<long> &generated_position,
                                                       int depth) {
  int base = (int) std::pow(base_exp, depth) * this->starting_base;
  CRDTAllocationStrategy strategy_at_depth = GetAllocationStrategyForDepth(depth);
  // if no positions, then probably its a new level and in a new level, the available identifiers can go from 0 to
  // base size computed for that level (base size is exponentially increased at each level)
  long current_level_from_before_position = !before.empty() ? before.at(0) : 0;
  long current_level_from_after_position = !after.empty() ? after.at(0) : base;
  long interval_between_positions = current_level_from_after_position - current_level_from_before_position;
  if (interval_between_positions > 1) {
    // we have enough space to add a new character without increasing depth of the tree
    // generate a new position based on strategy
    long new_position = GenerateNewPositionIdentifier(current_level_from_before_position,
                                                      current_level_from_after_position,
                                                      strategy_at_depth);
    generated_position.push_back(new_position);
    return generated_position;
  } else if (interval_between_positions == 1) {
    // there is still not enough space and we need to add a new level to the tree
    generated_position.push_back(current_level_from_before_position);
    if (!before.empty()) {
      before.erase(before.begin());
    }
    std::vector<long> vector;
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
  return std::vector<long>();
}

std::vector<long> CRDTManager::GeneratePositionBefore(int index) {
  ThrowCustomExceptionOnNegativeIndex(index);
  if (index == 0) {
    return std::vector<long>();
  }
  return this->characters->at(index - 1).GetPositions();
}

std::vector<long> CRDTManager::GeneratePositionAfter(int index) {
  ThrowCustomExceptionOnNegativeIndex(index);
  if (index >= this->characters->size()) {
    return std::vector<long>();
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

long CRDTManager::GenerateNewPositionIdentifier(long minimum,
                                                long maximum,
                                                CRDTAllocationStrategy allocation_strategy) const {
  // generate a random number between max & minimum, but within boundary
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_real_distribution<float> random_number(0.0, 1.0);
  // if maximum index - minimum index is less than boundary then the number will simply be between min + 1 & max
  // boundary strategy does not matter. since min + boundary or max - boundary will be out of range
  if (maximum - minimum < boundary) {
    minimum = minimum + 1;
  } else {
    // maximum - minimum >= boundary => possible to use both strategies
    if (allocation_strategy == BOUNDARY_MINUS) {
      // maximum remains same, since we need to choose a number near the maximum value so shift minimum ahead
      minimum = maximum - boundary;
    } else {
      // minimum remains same, since we need to choose a number near the minimum value, so shift maximum behind
      minimum = minimum + 1;
      maximum = minimum + this->boundary;
    }
  }
  // max & min are both set according to strategy, find a random number in between
  // better would be to create a uniform distribution of ints, and choose a number from them, but doing this so as to
  // avoid creating a new uniform distribution object.
  return (int) std::floor(random_number(gen) * (float) (maximum - minimum)) + minimum;
}

int CRDTManager::FindRemoteInsertPosition(CRDTCharacter remote_character) {
  int start = 0;
  int end = (int) this->characters->size() - 1;
  // if there are no characters instead, or the current character is supposed to be before the current start character
  if (this->characters->empty() || remote_character.ComparePositionTo(this->characters->at(start)) < 0) {
    return start;
  }
  // if the character to be inserted is at the last position
  if (remote_character.ComparePositionTo(this->characters->at(end)) > 0) {
    return this->characters->size();
  }
  // run binary search to find the correct insert position, much like in the TextFileContent.
  while ((start + 1) < end) {
    int mid = std::floor(start + (end - start) / 2);
    int compare_result = remote_character.ComparePositionTo(this->characters->at(mid));
    if (compare_result == 0) {
      return mid;
    } else if (compare_result < 0) {
      end = mid;
    } else if (compare_result > 0) {
      start = mid;
    }
  }
  // will be the case with odd number of characters (case like end = start + 1) at the end of while loop
  // in such cases, the correct insert position will either be the last recorded start or last recorded end
  return remote_character.ComparePositionTo(this->characters->at(start)) == 0 ? start : end;
}

int CRDTManager::FindRemoteDeletePosition(CRDTCharacter remote_character) {
  int start = 0;
  int end = (int) this->characters->size() - 1;
  if (this->characters->empty()) {
    throw CustomMessageException("Character to delete not present in CRDT. CRDT empty!");
  }
  while ((start + 1) < end) {
    int mid = std::floor(start + (end - start) / 2);
    int compare_result = remote_character.ComparePositionTo(this->characters->at(mid));
    if (compare_result == 0) {
      return mid;
    } else if (compare_result < 0) {
      end = mid;
    } else if (compare_result > 0) {
      start = mid;
    }
  }
  // The correct delete position outside the position has to be one of start or end
  if (remote_character.ComparePositionTo(this->characters->at(start)) == 0) {
    return start;
  }
  if (remote_character.ComparePositionTo(this->characters->at(end)) == 0) {
    return end;
  }
  std::string error_message = "Character to delete not present in CRDT!";
  error_message.append(remote_character.ToString());
  throw CustomMessageException(error_message);
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
