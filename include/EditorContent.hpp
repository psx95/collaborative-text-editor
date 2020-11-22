//
// Created by psx95 on 11/16/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_EDITORCONTENT_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_EDITORCONTENT_HPP_

#include "Cursor.hpp"
#include "TextFileContent.hpp"

/*!
 * @brief This class represents the current content that is visible on the GUI window.
 * @details The class contains various methods that allow manipulating the content visible on the screen.
 */
class EditorContent {
 private:
  Cursor cursor; // The cursor that is visible on the screen.
  TextFileContent &text_document; // Object to encapsulate all the text manipulation

 public:
  /*!
   * @brief Public constructor for the class.
   * @param text_document The TextFileContent object that encapsulates the actual text content that is visible on the
   * GUI window.
   */
  explicit EditorContent(TextFileContent &text_document);

  /*!
   * @brief Getter for the cursor visible on the screen.
   * @return The cursor object representing the cursor visible on the GUI window.
   */
  Cursor GetCursor();

  /*!
   * @brief This method inserts the given text at the current cursor position on screen.
   * @param txt The text to be inserted.
   */
  void InsertStringAtCursor(sf::String txt);

  /*!
   * @brief This method deletes a certain number of characters from the current cursor position.
   * @details The number of characters that are to be deleted are calculated from before the cursor.
   * @param number_of_characters The number of characters that need to be deleted.
   */
  void DeleteCharacterFromCursorPosition(int number_of_characters);

  /*!
   * @brief This method returns the total number of line in the given text content.
   * @return The current number of lines in the text document.
   */
  int GetNumberOfLines() const;

  /*!
   * @brief This method is responsible for returning the nth line from the visible text on the screen.
   * @param line_number The line position for the line that needs to be retrieved.
   * @return The retrieved line at a given position as a String.
   */
  sf::String GetLineAt(int line_number) const;

  /*!
   * @brief This method updates the cursor position by moving it one step towards right, if possible.
   * @details Moving cursor towards right won't be possible if it is already at the end of the text. If the cursor is
   * currently at the end of current line, this will move the cursor to the first column of the next line.
   */
  void MoveCursorRight();

  /*!
   * @brief This method updates the cursor position by moving it one step towards left, if possible.
   * @details Moving cursor towards right won't be possible if it is already at the beginning of the text. If the cursor
   * is currently at the start of current line, this will move the cursor to the first column of the previous line.
   */
  void MoveCursorLeft();

  /*!
   * @brief This method updates the cursor position by moving it one line above, if possible.
   * @details Moving cursor up will not be possible if the cursor is already at the first line of the text.
   */
  void MoveCursorUp();

  /*!
   * @brief This method updates the cursor position by moving it one line below, if possible.
   * @details Moving cursor down will not be possible if the cursor is already at the last line of the text.
   */
  void MoveCursorDown();

  std::string GetStringContent();
  std::vector<int> &GetLinePositions();

};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_EDITORCONTENT_HPP_
