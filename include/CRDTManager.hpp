//
// Created by psx95 on 11/27/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_CRDT_CRDTMANAGER_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_CRDT_CRDTMANAGER_HPP_

#include <map>

#include "CommonStructs.hpp"
#include "VersionVector.hpp"
#include "CRDTCharacter.hpp"

/*!
 * @brief This class handles all the CRDT operations and should be used to provide APIs to external classes to perform
 * tasks related to CRDT.
 * @details The most important function for this class is to generate CRDTActions for local insert/delete operations
 * and the converting incoming CRDTs (Conflict Free Replicated Data Type) to their corresponding local actions, along
 * with maintaining a log of the operations.
 * Algorithm used for allocation for globally unique sequences is called \ref https://hal.archives-ouvertes.fr/hal-00921633/document [("LSEQ")]
 * and is adapted from the paper mentioned in the link.
 */
class CRDTManager {
 private:
  std::string &site_id; // should be unique across all clients, could use UUID or IP-port combo
  std::map<int, CRDTAllocationStrategy> *strategy_map{}; // map maintains strategy used at each level
  std::vector<CRDTCharacter> *characters{}; // vector maintaining the CRDTCharacters present in the text document
  int starting_base = 16; // the starting base used by the allocation strategy
  int base_exp = 2; // when the base is increased exp is the base of the power to which the base increased.
  const int boundary = 20; // fixed boundary

  /*!
   * @brief Private helper that generates a CRDTCharacter for a corresponding local insert operation performed by user.
   * @param c The actual character value that needs to be inserted.
   * @param position_in_doc The position of the insert (index) in the document content.
   * @param site_counter The current site counter.
   * @return the Generated CRDTCharacter.
   */
  CRDTCharacter GenerateCRDTCharacter(char c, int position_in_doc, int site_counter);

  /*!
   * @brief This method generates a new & unique position between two positions.
   * @details This method is implemented with a recursive approach.
   * @param before A vector of longs, defining the position after which the new character needs to be inserted.
   * @param after A vector of longs, defining the position before which the new character needs to be inserted.
   * @param [out] generated_position The array containing newly generated position for the character.
   * @param depth The depth of the internal tree-like structure (actually represented using the vectors).
   * @return A vector of identifier pairs, defining the globally unique position of the character that needed to be inserted.
   */
  std::vector<std::pair<long, std::string>> GeneratePositionBetween(std::vector<std::pair<long, std::string>> &before,
                                                                    std::vector<std::pair<long, std::string>> &after,
                                                                    std::vector<std::pair<long,
                                                                                          std::string>> &generated_position,
                                                                    int depth = 0);

  std::vector<std::pair<long, std::string>> GeneratePositionBefore(int index);
  std::vector<std::pair<long, std::string>> GeneratePositionAfter(int index);
  CRDTAllocationStrategy GetAllocationStrategyForDepth(int depth);
  std::pair<long, std::string> GenerateNewPositionIdentifier(long minimum,
                                                             long maximum,
                                                             CRDTAllocationStrategy allocation_strategy) const;

  int FindRemoteInsertPosition(CRDTCharacter remote_character);
  int FindRemoteDeletePosition(CRDTCharacter remote_character);
  static void ThrowCustomExceptionOnNegativeIndex(int index);

 public:
  /*!
   * @brief Public constructor for CRDTManager.
   * @param site_id The site id for the node to which this CRDTManager belongs.
   */
  explicit CRDTManager(std::string &site_id);

  /*!
   * @brief This method generates a CRDTAction whichcharacters  can be sent to other connected peers for an insert operation.
   * @details CRDTAction should be generated for each local insert.
   * @param c The actual character value which was inserted by the user.
   * @param index The index in the actual content string at which the character was inserted.
   * @param site_counter The updated site counter, as a result of the local insert.
   * @return CRDTAction corresponding to the local insert made by the user.
   */
  struct CRDTAction GenerateCRDTActionForLocalInsert(char c, int index, int site_counter);

  /*!
   * @brief This method generates a CRDTAction which can be sent to other connected peers for a delete operation.
   * @param index The index in the actual content string at which the character was inserted.
   * @param site_counter The updated site counter, as a result of the local delete.
   * @return CRDTAction corresponding to the local delete made by the user.
   */
  struct CRDTAction GenerateCRDTActionForLocalDelete(int index, int site_counter);

  /*!
   * @brief This method can be used to generate the information required to locally process a remote insert.
   * @details The method computes the appropriate position for inserting the CRDTCharacter passed in the CRDTAction on
   * the local editor.
   * @param remote_action The remote CRDTAction that triggered a local insert on the current node.
   * @return A pair containing the character inserted & its computed position for insert on the current node.
   */
  std::pair<std::string, int> GenerateStringInsertInfoFromRemoteInsert(struct CRDTAction &remote_action);

  /*!
   * @brief This method is used to generate the information required to locally process a remote delete.
   * @details This method computes the appropriate position in the local text, from which a character needs to be
   * deleted.
   * @param remote_action The remote CRDTAction that triggered a local delete on the current node.
   * @return The local index of the character that needs to be deleted.
   */
  int GenerateDeleteInfoFromRemoteDelete(struct CRDTAction &remote_action);

  /*!
   * @brief Getter for CRDTCharacters, this method should not be used except for purposes of unit testing.
   * @return The vector containing all the CRDTCharacters managed by the CRDTManager.
   */
  std::vector<CRDTCharacter> *GetCRDTCharacters() const;

  /*!
   * @brief Getter for the current Site ID.
   * @return The site ID (A UUID) for the this peer.
   */
  std::string &GetSiteId() const;

  ~CRDTManager();
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_CRDT_CRDTMANAGER_HPP_
