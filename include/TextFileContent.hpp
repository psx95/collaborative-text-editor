//
// Created by psx95 on 11/20/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_TEXTFILE_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_TEXTFILE_HPP_

#include <SFML/System/String.hpp>
#include <vector>

/*!
 * @brief This class is a wrapper around the actual string content that is displayed on the GUI.
 * @details The class offers additional methods that allow for convenient APIs to manipulate and view the string content
 * as a collection of lines rather than a single huge string. The class maybe used to abstract the actual source of the
 * string content that is visible on the GUI.
 */
class TextFileContent {
 private:
  sf::String string_content;
  std::vector<int> line_positions{};

  int GetStringPositionFromCursorPosition(int line_number, int column_number);

 public:
  /*!
   * @brief The public constructor for the TextFileContent class.
   */
  explicit TextFileContent();

  /*!
   * @brief This method extracts the substring that represents a certain visual text line on the editor window.
   * @param line_number The visual line number corresponding to which the text needs to be extracted.
   * @return The extracted substring from the actual string that represent the line with the passed line_number.
   */
  sf::String GetLine(int line_number);

  /*!
   * @brief This method returns the total number of lines in the current displayed text on screen.
   * @return The number of lines of text on screen.
   */
  int GetNumberOfTotalLines() const;

  /*!
   * @brief This method returns the number of characters in a line at the given line_number.
   * @param line_number The line number for the line whose number of characters are required.
   * @return The number of characters in a line located at the given number.
   */
  int GetNumberOfCharactersInLine(int line_number);

  /*!
   * @brief This method is responsible for adding text at a given position.
   * @details The position is determined by the combination of line number and column number.
   * @param text The text that needs to be inserted at the given position.
   * @param line_number The line number at which the text needs to be inserted.
   * @param column_number The column number at which the text needs to be inserted.
   */
  void AddTextAtPosition(sf::String &text, int line_number, int column_number);

  /*!
   * @brief This method is responsible for removing a certain amount of text from a given position.
   * @details The position is determined by the combination of line number and column number. The text will be deleted
   * from before the current position.
   * @param amount The number of characters in the text that need to be deleted.
   * @param line_number The line number at which the text needs to be inserted.
   * @param column_number The column number at which the text needs to be inserted.
   */
  void RemoveTextFromPosition(int amount, int line_number, int column_number);
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_TEXTFILE_HPP_
