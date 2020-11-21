//
// Created by psx95 on 11/16/20.
//

#include <iostream>
#include "EditorContent.hpp"
EditorContent::EditorContent(TextFileContent &text_file_content) : text_document(text_file_content) {
  this->cursor = Cursor();
}

Cursor EditorContent::GetCursor() {
  return this->cursor;
}

void EditorContent::InsertStringAtCursor(sf::String txt) {
  int line_number = this->cursor.GetLineNumber();
  int column_number = this->cursor.GetColumnNumber();
  this->text_document.AddTextAtPosition(txt, line_number, column_number);
  for (int i = 0; i < txt.getSize(); i++) {
    this->MoveCursorRight();
  }
}

void EditorContent::InsertCharacterAtPosition(int column_number, int line_number) {

}

void EditorContent::DeleteCharacterFromCursorPosition() {
  cursor.MoveCursorLeft();
}

void EditorContent::DeleteCharacterFromPosition(int column_number, int line_number) {

}

std::string EditorContent::GetStringContent() {

}

std::vector<int> &EditorContent::GetLinePositions() {

}

void EditorContent::MoveCursorRight() {
  int characters_in_current_line = this->text_document.GetNumberOfCharactersInLine(this->cursor.GetLineNumber());
  if (this->cursor.GetColumnNumber() >= characters_in_current_line) {
    int new_cursor_line = std::min(this->cursor.GetLineNumber() + 1, this->text_document.GetNumberOfTotalLines());
    this->cursor.MoveCursorToPosition(0, new_cursor_line, true);
  } else {
    this->cursor.MoveCursorRight(true);
  }
}

void EditorContent::MoveCursorLeft() {

}

void EditorContent::MoveCursorUp() {

}

void EditorContent::MoveCursorDown() {

}

int EditorContent::GetNumberOfLines() const {
  return this->text_document.GetNumberOfTotalLines();
}

sf::String EditorContent::GetLineAt(int line_number) const {
  return text_document.GetLine(line_number);
}
