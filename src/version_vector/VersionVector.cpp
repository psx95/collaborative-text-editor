//
// Created by tsnaik on 11/27/20.
//

#include "VersionVector.hpp"

std::vector<CRDTAction> VersionVector::ProcessRemoteAction(CRDTAction &action) {
  return std::vector<CRDTAction>();
}

void VersionVector::IncrementSiteCounter() {

}

int VersionVector::GetSiteCounter() {
  return 0;
}

