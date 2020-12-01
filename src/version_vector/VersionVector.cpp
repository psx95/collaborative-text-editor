//
// Created by tsnaik on 11/27/20.
//

#include "VersionVector.hpp"

VersionVector::VersionVector(std::string &site_id) : site_id(site_id) {
  CreateMapEntry(site_id);
}

std::vector<CRDTAction> VersionVector::ProcessRemoteAction(CRDTAction &action) {
  std::vector<CRDTAction> actions;
  std::string id = action.SiteId();

  CreateMapEntry(id);

  VersionInfo &info = this->versions[id];

  if (info.HasSeenCounter(action.Counter())) {
    return actions;
  } else {
    info.AddToSeenCounters(action.Counter());
  }

  if (action.Operation() == INSERT) {
    actions.push_back(action);
    info.IncrementCounterBy(1);
  } else {
    info.AddToDeletionBuffer(action);
  }

  std::vector<CRDTAction> bufferOP = this->ProcessDeletionBuffer(info);
  actions.insert(actions.end(), bufferOP.begin(), bufferOP.end());

  return actions;
}

void VersionVector::IncrementSiteCounter() {
  this->site_counter += 1;
}

int VersionVector::GetSiteCounter() {
  return this->site_counter;
}

void VersionVector::CreateMapEntry(std::string &id) {
  if (this->versions.count(id) == 0) {
    VersionInfo i(id);
    this->versions[id] = i;
  }
}

std::vector<CRDTAction> VersionVector::ProcessDeletionBuffer(VersionInfo &version_info) {
  std::vector<CRDTAction> ready_to_go;

  for (auto it = version_info.GetDeletionBuffer().begin(); it != version_info.GetDeletionBuffer().end();) {
    if (it->Counter() <= version_info.GetCounter()) {
      ready_to_go.push_back(*it);
      version_info.IncrementCounterBy(1);
      it = version_info.GetDeletionBuffer().erase(it);
    } else {
      ++it;
    }
  }

  return ready_to_go;
}


