//
// Created by psx95 on 11/26/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_EDITORCALLBACKS_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_EDITORCALLBACKS_HPP_

/*!
 * @brief This class acts like interface callbacks for the EditorContent. This interface will allow implementing classes
 * to know of certain events that occur in the EditorContent.
 */
class EditorCallbacks {
 public:
  /*!
   * @brief This method should be called to notify whenever a character is inserted by the user on the editor GUI.
   * @details In case multiple characters are inserted, this gives the starting location at which the text was inserted.
   * @param text The text user inserted into the editor GUI.
   * @param index The location in the actual string content where the text was inserted.
   */
  virtual void OnLocalInsert(sf::String &text, int index);

  /*!
   * @brief This method should be called to notify whenever the user deletes a character from the editor GUI.
   * @param index The location in the actual string content from where the text was deleted.
   */
  virtual void OnLocalDelete(int index);
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_EDITORCALLBACKS_HPP_
