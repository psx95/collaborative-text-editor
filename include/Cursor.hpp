//
// Created by psx95 on 11/16/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_CURSOR_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_CURSOR_HPP_

#include <SFML/Graphics/RenderWindow.hpp>
class Cursor {
 private:
  int line_number;
  int column_number;
  int max_line_number;
  int max_column_number;

  void UpdateCursorPosition(int _column_number, int _line_number);

 public:
  explicit Cursor();
  std::pair<int, int> GetCurrentPosition();
  void MoveCursorUp();
  void MoveCursorDown();
  void MoveCursorLeft();
  void MoveCursorRight(bool insert_char);
  void MoveCursorToPosition(int _column_number, int _line_number);
  void UpdateMaxLineNumber(int updated_max_line_number);
  void UpdateMaxColumnNumber(int updated_max_column_number);
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_CURSOR_HPP_
