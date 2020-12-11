//
// Created by psx95 on 11/29/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_CRDT_CRDTCHARACTER_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_CRDT_CRDTCHARACTER_HPP_

#include <string>
#include <vector>

/*!
 * @brief This class represents a single globally unique character that can be inserted in the collaborative text
 * editor. These objects are created by CRDTManager automatically whenever the user performs an insert operation on
 * the editor window.
 */
class CRDTCharacter {
 private:
  char value{}; // the value of the character that is inserted
  int counter{}; // the current site counter, from the version vector
  std::string site_id; // the site id of the node that generated this character
  // the positions array that can be used to determine the globally unique location of the current object
  std::vector<long> positions;

  CRDTCharacter() = default; // the default constructor cannot be used by external classes

 public:
  /*!
   * @brief Public constructor that can be used to create instances of this object
   * @param value The character value for the CRDTCharacter.
   * @param counter The current site counter of the node.
   * @param site_id The globally unique site id of the node.
   * @param positions The positions array used to determine the globally unique positions for the in the document.
   */
  explicit CRDTCharacter(char value, int counter, std::string &site_id, std::vector<long> &positions);

  /*!
   * @brief Getter for the value character.
   * @return The character value held by this object.
   */
  char GetValue() const;

  /*!
   * @brief Getter for the site counter value.
   * @return The site counter value held by the current object.
   */
  int GetCounter() const;

  /*!
   * @brief Getter for the site id value.
   * @return The site id value of the peer that generated this character.
   */
  const std::string &GetSiteId() const;

  /*!
   * @brief Getter for the positions array that define the globally unique position.
   * @return The positions array which can be used to determine the position of the array in document.
   */
  const std::vector<long> &GetPositions() const;

  /*!
   * @brief This method compares positions of the current CRDTCharacter with another CRDTCharacter.
   * @details The method returns an int
   * @param other_character The other character to which current character's position is to be compared.
   * @return An integer. 0 if the character positions are same, 1 if the current character should come after the
   * other_character, -1 if the current character should appear before the other_character.
   */
  int ComparePositionTo(CRDTCharacter &other_character);

  /*!
   * @brief A method to get the string representation of the CRDTCharacter object.
   * @return A string displaying all member variables for the object in human-readable form.
   */
  std::string ToString();
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_CRDT_CRDTCHARACTER_HPP_
