//
// Created by tsnaik on 11/28/20.
//

#include "VersionInfo.hpp"

VersionInfo::VersionInfo(std::string &site_id) : site_id(site_id) {}

const std::string &VersionInfo::GetSiteId() const {
  return site_id;
}

int VersionInfo::GetCounter() const {
  return counter;
}

std::set<struct CRDTAction> &VersionInfo::GetDeletionBuffer() {
  return deletion_buffer;
}

void VersionInfo::AddToDeletionBuffer(struct CRDTAction &action) {
  this->deletion_buffer.insert(action);
}

VersionInfo::VersionInfo() {
  this->site_id = "-1";
}

void VersionInfo::IncrementCounterBy(int value) {
  this->counter += value;
}

void VersionInfo::AddToSeenCounters(int count) {
  seen_counters.insert(count);
}

bool VersionInfo::HasSeenCounter(int count) {
  return seen_counters.count(count) != 0;
}
