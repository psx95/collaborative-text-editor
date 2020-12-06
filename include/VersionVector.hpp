//
// Created by tsnaik on 11/27/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_VERSIONVECTOR_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_VERSIONVECTOR_HPP_
#include <vector>
#include <map>
#include "CommonStructs.hpp"
#include "VersionInfo.hpp"

/*!
 * @brief Processes all incoming remote operations and makes sure that the deletion operations are not applied before inserts.
 * @details It hold any incoming delete operation in a buffer if there is a pending operation from that peer. And it
 * sends the delete operation for processing if the pending operations have arrived.
 */
class VersionVector {
 private:
  std::string &site_id;
  int site_counter = -1;
  std::map<std::string, VersionInfo> versions;
  void CreateMapEntry(std::string &id);
  void UpdateCurrentMap();
  std::vector<CRDTAction> ProcessDeletionBuffer(VersionInfo &version_info);

 public:
  /*!
   * @brief Initialize an instance with the current site id.
   * @param site_id Site id of the this client
   */
  explicit VersionVector(std::string &site_id);

  /*!
   * @brief Processes any incoming actions from remote.
   * @param Action to be processed.
   * @return List of all actions that are ready to be applied.
   */
  std::vector<CRDTAction> ProcessRemoteAction(CRDTAction &action, std::string &site_id, int site_version);

  /*!
   * @brief Increment the site counter of this client. Should be called before a local operation is broadcast.
   */
  void IncrementSiteCounter();

  /*!
   * Get the current site counter of this client. Should be included when broadcasting local actions.
   * @return Current site counter.
   */
  int GetSiteCounter();
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_VERSIONVECTOR_HPP_
