//
// Created by psx95 on 11/29/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_CRDT_CRDTCHARACTER_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_CRDT_CRDTCHARACTER_HPP_

#include <string>
#include <vector>

class CRDTCharacter {
 private:
  char value;
  int counter;
  std::string site_id;
  std::vector<int> positions;

 public:
  explicit CRDTCharacter(char value, int counter, std::string &site_id, std::vector<int> &positions);

  char GetValue() const;
  int GetCounter() const;
  const std::string &GetSiteId() const;
  const std::vector<int> &GetPositions() const;
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_CRDT_CRDTCHARACTER_HPP_
