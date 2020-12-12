//
// Created by psx95 on 11/29/20.
//

#include "CRDTCharacter.hpp"
CRDTCharacter::CRDTCharacter(char value, int counter, std::string &site_id, std::vector<std::pair<long, std::string>> &positions) {
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

const std::vector<std::pair<long, std::string>> &CRDTCharacter::GetPositions() const {
  return positions;
}

int CRDTCharacter::ComparePositionTo(CRDTCharacter &other_character) {
  std::vector<std::pair<long, std::string>> other_position = other_character.GetPositions();
  int min_length = std::min(other_position.size(), this->positions.size());
  for (int i = 0; i < min_length; i++) {
    int digit_compare_result = (int) (this->positions.at(i).first - other_position.at(i).first);
    int identifier_compare_result = digit_compare_result;
    if (digit_compare_result == 0) {
      if (this->positions.at(i).second < other_position.at(i).second){
        identifier_compare_result = -1;
      } else if (this->positions.at(i).second > other_position.at(i).second) {
        identifier_compare_result = 1;
      } else {
        identifier_compare_result = 0;
      }
    }
    if (identifier_compare_result != 0) {
      return identifier_compare_result;
    }
  }
  // so far all positions were same with same identifiers, so check for size inequality
  int compare_result = (int) (this->positions.size() - other_position.size());
  if (compare_result < 0) {
    return -1;
  }
  if (compare_result > 0) {
    return 1;
  }
  return 0;
}

std::string CRDTCharacter::ToString() {
  std::string crdt("\nCRDT Character:");
  crdt.append("\nValue: ").append(std::to_string(this->value))
      .append("\nPositions: ");
  for (const std::pair<long, std::string>& position : this->positions) {
    crdt.append(std::to_string(position.first)).append(", ");
  }
  return crdt;
}
