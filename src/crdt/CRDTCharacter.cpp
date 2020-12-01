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
