//
// Created by psx95 on 11/16/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_CURSOR_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_CURSOR_HPP_

#include <SFML/Graphics/RenderWindow.hpp>
// This class represents the visual cursor and is mainly responsible for maintaining the cursor's properties.
class Cursor {
 private:
  int line_number; // current line number
  int column_number; // current column number

  void UpdateCursorPosition(int _column_number, int _line_number);

 public:
  /*!
   * @brief The public constructor for the class.
   */
  explicit Cursor();

  /*!
   * @brief This method is responsible for providing the current cursor position as a pair of ints.
   * @details The first element of the pair represents the column number at which the cursor is currently present and
   * the second element is responsible for providing the line number of the cursor.
   * @return The current position of cursor as a std::pair of ints.
   */
  std::pair<int, int> GetCurrentPosition() const;

  /*!
   * @brief A convenience method and is used to retrieve the current line number at which cursor is currently present.
   * @return The current line number for the cursor.
   */
  int GetLineNumber() const;

  /*!
   * @brief A convenience method and is used to retrieve the current column number at which cursor is currently present.
   * @return The current column number for the cursor.
   */
  int GetColumnNumber() const;

  /*!
   * @brief This method moves the cursor up by one line.
   */
  void MoveCursorUp();

  /*!
   * @brief This method is responsible for moving the cursor down by one line.
   */
  void MoveCursorDown();

  /*!
   * @brief This method is responsible for moving the cursor left by one column, if possible.
   */
  void MoveCursorLeft();

  /*!
   * @brief This method is responsible for moving the cursor right by one column.
   */
  void MoveCursorRight();

  /*!
   * @brief This method can be used to update the current position of the cursor to any other position.
   * @param _column_number The new column number to which the cursor needs to be moved to.
   * @param _line_number  The new line number to which the cursor needs to be moved to.
   */
  void MoveCursorToPosition(int _column_number, int _line_number);
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_CURSOR_HPP_
