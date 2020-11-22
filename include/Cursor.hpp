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
  int max_column_number;

  void UpdateCursorPosition(int _column_number, int _line_number);

 public:
  explicit Cursor();
  std::pair<int, int> GetCurrentPosition();
  int GetLineNumber() const;
  int GetColumnNumber() const;
  void MoveCursorUp();
  void MoveCursorDown();
  void MoveCursorLeft();
  void MoveCursorRight();
  void MoveCursorToPosition(int _column_number, int _line_number, bool update_max_column = false);
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_CURSOR_HPP_
