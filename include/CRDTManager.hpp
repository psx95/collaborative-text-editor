//
// Created by psx95 on 11/27/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_CRDT_CRDTMANAGER_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_CRDT_CRDTMANAGER_HPP_

#include "CommonStructs.hpp"
class CRDTManager {
 private:
  std::string &site_id; // should be unique across all clients, could use UUID or IP-port combo

 public:
  explicit CRDTManager(std::string &site_id);

  struct CRDTAction GenerateCRDTActionForLocalInsert(std::string &text, int index);

  struct CRDTAction GenerateCRDTActionForLocalDelete(int index);

  std::pair<std::string, int> GenerateStringInsertInfoFromRemoteInsert(struct CRDTAction &remote_action);

  int GenerateDeleteInfoFromRemoteDelete(struct CRDTAction &remote_action);
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_CRDT_CRDTMANAGER_HPP_
