//
// Created by tsnaik on 11/27/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_VERSIONVECTOR_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_VERSIONVECTOR_HPP_
#include <vector>
#include "CommonStructs.hpp"

class VersionVector {
  std::vector<CRDTAction> ProcessRemoteAction(CRDTAction &action);

  void IncrementSiteCounter();

  int GetSiteCounter();
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_VERSIONVECTOR_HPP_
