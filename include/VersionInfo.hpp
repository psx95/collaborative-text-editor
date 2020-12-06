//
// Created by tsnaik on 11/28/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_VERSION_VECTOR_VERSIONINFO_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_VERSION_VECTOR_VERSIONINFO_HPP_

#include <string>
#include <set>
#include <unordered_set>
#include "CommonStructs.hpp"

struct BufferItem {
  std::string site_id;
  int site_counter;
  struct CRDTAction character;

  // overriding < operator for std::set
  bool operator<(const BufferItem &msgObj) const {
    return (this->site_counter < msgObj.site_counter);
  }
};

/*!
 * @brief This class is used by version vector to store versions of each client. Maintains a deletion buffer for each client.
 */
class VersionInfo {
 private:
  std::string site_id;
  int counter = 0; // count of #operations processed so far
  std::set<BufferItem> deletion_buffer;
  std::unordered_set<int> seen_counters;

 public:
  explicit VersionInfo();
  explicit VersionInfo(std::string &site_id);
  const std::string &GetSiteId() const;
  int GetCounter() const;
  void IncrementCounterBy(int value);
  std::set<struct BufferItem> &GetDeletionBuffer();
  void AddToDeletionBuffer(struct BufferItem &item);
  void AddToSeenCounters(int count);
  bool HasSeenCounter(int count);
  void SetCounter(int counter);
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_VERSION_VECTOR_VERSIONINFO_HPP_
