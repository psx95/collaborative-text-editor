//
// Created by psx95 on 11/16/20.
//

#include <iostream>
#include "EditorContent.hpp"
EditorContent::EditorContent() {
  this->cursor = Cursor();
  this->content = "";
  this->line_positions.push_back(0);
}

Cursor EditorContent::GetCursor() {
  return this->cursor;
}

void EditorContent::InsertCharacterAtCursor(char x) {
  std::pair<int, int> cursor_position = cursor.GetCurrentPosition();
  int content_position = GetCharacterPositionInStringFromEditor(cursor_position.first, cursor_position.second);
  content.insert(content_position,1, x);
  if (x == '\n' || x == 13) {
    line_positions.push_back(content_position);
    std::sort(line_positions.begin(), line_positions.end());
    cursor.MoveCursorToPosition(0, cursor_position.second + 1);
  } else {
    cursor.MoveCursorRight(true);
  }
}

void EditorContent::InsertCharacterAtPosition(int column_number, int line_number) {

}

void EditorContent::DeleteCharacterFromCursorPosition() {
  cursor.MoveCursorLeft();
}

void EditorContent::DeleteCharacterFromPosition(int column_number, int line_number) {

}

int EditorContent::GetCharacterPositionInStringFromEditor(int column_number, int line_number) {
  if (line_number >= line_positions.size()) {
    std::cerr << "Error cannot get position for this line " << std::endl;
  }
  //std::cout << "Character position in String " << line_positions.at(line_number) + column_number << std::endl;
  return line_positions.at(line_number) + column_number;
}

std::string EditorContent::GetStringContent() {
  return this->content;
}

std::vector<int> &EditorContent::GetLinePositions() {
  return this->line_positions;
}
