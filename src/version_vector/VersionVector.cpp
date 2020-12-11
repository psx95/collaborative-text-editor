//
// Created by tsnaik on 11/27/20.
//

#include "VersionVector.hpp"

VersionVector::VersionVector(std::string &site_id) : site_id(site_id) {
  CreateMapEntry(site_id);
}

std::vector<CRDTAction> VersionVector::ProcessRemoteAction(CRDTAction &action, std::string &s_id, int site_version) {
  std::vector<CRDTAction> actions;
  if (s_id == this->site_id) {
    return actions;
  }

  std::string id = action.SiteId();

  UpdateCurrentMap();
  CreateMapEntry(id);
  CreateMapEntry(s_id);

  VersionInfo &info = this->versions[id];

  if (versions[s_id].HasSeenCounter(site_version)) {
    return actions;
  } else {
    versions[s_id].AddToSeenCounters(site_version);
  }

  if (action.Operation() == INSERT) {
    actions.push_back(action);
    info.IncrementCounterBy(1);
  } else {
    BufferItem buffer_item{
        .site_id =  s_id,
        .site_counter = site_version,
        .character = action
    };
    info.AddToDeletionBuffer(buffer_item);
  }

  for (auto &version : versions) {
    std::vector<CRDTAction> bufferOP = this->ProcessDeletionBuffer(version.second);
    actions.insert(actions.end(), bufferOP.begin(), bufferOP.end());
  }

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
    if (it->character.Counter() <= version_info.GetCounter()) {
      ready_to_go.push_back(it->character);
      versions[it->site_id].IncrementCounterBy(1);
      it = version_info.GetDeletionBuffer().erase(it);
    } else {
      ++it;
    }
  }

  return ready_to_go;
}
void VersionVector::UpdateCurrentMap() {
  this->versions[site_id].SetCounter(GetSiteCounter());
}


