//
// Created by psx95 on 11/16/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_EDITORCONTENT_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_EDITORCONTENT_HPP_

#include "Cursor.hpp"
class EditorContent {
 private:
  // Text content
  Cursor cursor;
  char* content;

 public:
  explicit EditorContent();

  Cursor GetCursor();

  void InsertCharacterAtCursor(char x);
  void InsertCharacterAtPosition(int column_number, int line_number);
  void DeleteCharacterFromCursorPosition();
  void DeleteCharacterFromPosition(int column_number, int line_number);

};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_EDITORCONTENT_HPP_
