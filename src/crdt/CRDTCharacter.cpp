//
// Created by psx95 on 11/29/20.
//

#include "CRDTCharacter.hpp"
CRDTCharacter::CRDTCharacter(char value, int counter, std::string &site_id, std::vector<long> &positions) {
  this->value = value;
  this->counter = counter;
  this->site_id = site_id;
  this->positions = positions;
}

char CRDTCharacter::GetValue() const {
  return value;
}

int CRDTCharacter::GetCounter() const {
  return counter;
}

const std::string &CRDTCharacter::GetSiteId() const {
  return site_id;
}

const std::vector<long> &CRDTCharacter::GetPositions() const {
  return positions;
}

int CRDTCharacter::ComparePositionTo(CRDTCharacter &other_character) {
  std::vector<long> other_position = other_character.GetPositions();
  int min_length = std::min(other_position.size(), this->positions.size());
  for (int i = 0; i < min_length; i++) {
    int compare_result = (int) (this->positions.at(i) - other_position.at(i));
    if (compare_result != 0) {
      return compare_result;
    }
  }
  // so far all positions were same, so check for size inequality
  int compare_result = (int) (this->positions.size() - other_position.size());
  if (compare_result < 0) {
    return -1;
  }
  if (compare_result > 0) {
    return 1;
  }
  return 0;
}
