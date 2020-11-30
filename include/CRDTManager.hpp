//
// Created by psx95 on 11/27/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_CRDT_CRDTMANAGER_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_CRDT_CRDTMANAGER_HPP_

#include <map>

#include "CommonStructs.hpp"
#include "VersionVector.hpp"
#include "CRDTCharacter.hpp"

class CRDTManager {
 private:
  std::string &site_id; // should be unique across all clients, could use UUID or IP-port combo
  std::map<int, CRDTAllocationStrategy> *strategy_map{};
  std::vector<struct CRDTCharacter> *characters{};
  int starting_base = 16;
  int base_multiple = 2;
  const int boundary = 20;

  CRDTCharacter GenerateCRDTCharacter(char c, int position_in_doc, int site_counter);
  std::vector<int> GeneratePositionBetween(std::vector<int> &before,
                                           std::vector<int> &after,
                                           std::vector<int> &generated_position,
                                           int depth = 0);

  std::vector<int> GeneratePositionBefore(int index);
  std::vector<int> GeneratePositionAfter(int index);
  CRDTAllocationStrategy GetAllocationStrategyForDepth(int depth);
  int GenerateNewPositionIdentifier(int minimum, int maximum, CRDTAllocationStrategy allocation_strategy);
  static void ThrowCustomExceptionOnNegativeIndex(int index);

 public:
  explicit CRDTManager(std::string &site_id);

  struct CRDTAction GenerateCRDTActionForLocalInsert(char c, int index, int site_counter);

  struct CRDTAction GenerateCRDTActionForLocalDelete(int index, int site_counter);

  std::pair<std::string, int> GenerateStringInsertInfoFromRemoteInsert(struct CRDTAction &remote_action);

  int GenerateDeleteInfoFromRemoteDelete(struct CRDTAction &remote_action);

  ~CRDTManager();
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_CRDT_CRDTMANAGER_HPP_
