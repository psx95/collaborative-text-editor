//
// Created by psx95 on 11/27/20.
//

#include <CustomMessageException.hpp>
#include "CRDTManager.hpp"

CRDTManager::CRDTManager(int site_id) {
  this->site_id = site_id;
}

struct CRDTAction CRDTManager::GenerateCRDTActionForLocalInsert(std::string &text, int index) {
  throw CustomMessageException("Not Implemented yet");
}

struct CRDTAction CRDTManager::GenerateCRDTActionForLocalDelete(int index) {
  throw CustomMessageException("Not implemented yet");
}

std::pair<std::string, int> CRDTManager::GenerateStringInsertInfoFromRemoteInsert(CRDTAction &remote_action) {
  return std::pair<std::string, int>();
}

int CRDTManager::GenerateDeleteInfoFromRemoteDelete(CRDTAction &remote_action) {
  return 0;
}
