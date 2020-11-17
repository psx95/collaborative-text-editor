//
// Created by psx95 on 11/16/20.
//

#include "EditorContent.hpp"
EditorContent::EditorContent() {
  this->cursor = Cursor();
}

Cursor EditorContent::GetCursor() {
  return this->cursor;
}

void EditorContent::InsertCharacterAtCursor(char x) {

}

void EditorContent::InsertCharacterAtPosition(int column_number, int line_number) {

}

void EditorContent::DeleteCharacterFromCursorPosition() {

}

void EditorContent::DeleteCharacterFromPosition(int column_number, int line_number) {

}
