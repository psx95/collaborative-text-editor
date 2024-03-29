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
  int inserted_position = this->text_document.AddTextAtPosition(txt, line_number, column_number);
  if (inserted_position < 0) {
    return;
  }
  for (int i = 0; i < txt.getSize(); i++) {
    this->MoveCursorRight();
  }
  callbacks->OnLocalInsert(txt, inserted_position);
}

void EditorContent::DeleteCharacterFromCursorPosition(int number_of_characters) {
  int line_number = this->cursor.GetLineNumber();
  int column_number = this->cursor.GetColumnNumber();
  if (line_number == 0 && column_number == 0) {
    return;
  }
  int deleted_position = this->text_document.RemoveTextFromPosition(number_of_characters, line_number, column_number);
  if (deleted_position < 0) {
    return;
  }
  for (int i = 0; i < number_of_characters; i++) {
    this->MoveCursorLeft();
  }
  callbacks->OnLocalDelete(deleted_position);
}

void EditorContent::MoveCursorRight() {
  if (this->cursor.GetLineNumber() >= this->text_document.GetNumberOfTotalLines()) {
    return;
  }
  int characters_in_current_line = this->text_document.GetNumberOfCharactersInLine(this->cursor.GetLineNumber());
  if (this->cursor.GetColumnNumber() >= characters_in_current_line) {
    int new_cursor_line = std::min(this->cursor.GetLineNumber() + 1, this->text_document.GetNumberOfTotalLines() - 1);
    // if cursor is already at the same line, no need to update => usually happens when cursor reaches the last line
    if (new_cursor_line != cursor.GetLineNumber()) {
      this->cursor.MoveCursorToPosition(0, new_cursor_line);
    }
  } else {
    this->cursor.MoveCursorRight();
  }
}

void EditorContent::MoveCursorLeft() {
  if (this->cursor.GetLineNumber() >= this->text_document.GetNumberOfTotalLines()) {
    int number_characters_in_last_line =
        this->text_document.GetNumberOfCharactersInLine(this->text_document.GetNumberOfTotalLines() - 1);
    this->cursor.MoveCursorToPosition(number_characters_in_last_line, this->text_document.GetNumberOfTotalLines() - 1);
    return;
  }
  if (this->cursor.GetColumnNumber() > this->text_document.GetNumberOfCharactersInLine(this->cursor.GetLineNumber())) {
    this->cursor.MoveCursorToPosition(this->text_document.GetNumberOfCharactersInLine(this->cursor.GetLineNumber()),
                                      this->cursor.GetLineNumber());
    return;
  }
  if (this->cursor.GetColumnNumber() == 0) {
    int new_cursor_line = std::max(this->cursor.GetLineNumber() - 1, 0);
    if (new_cursor_line != cursor.GetLineNumber()) {
      int characters_in_new_line = this->text_document.GetNumberOfCharactersInLine(new_cursor_line);
      this->cursor.MoveCursorToPosition(characters_in_new_line, new_cursor_line);
    }
  } else {
    this->cursor.MoveCursorLeft();
  }
}

void EditorContent::MoveCursorUp() {
  // if the cursor is at a invalid line (line that no longer exist)
  if (this->cursor.GetLineNumber() >= this->text_document.GetNumberOfTotalLines()) {
    int number_characters_in_last_line =
        this->text_document.GetNumberOfCharactersInLine(this->text_document.GetNumberOfTotalLines() - 1);
    this->cursor.MoveCursorToPosition(number_characters_in_last_line, this->text_document.GetNumberOfTotalLines() - 1);
    return;
  }
  if (this->cursor.GetLineNumber() > 0) {
    int number_characters_in_prev_line =
        this->text_document.GetNumberOfCharactersInLine(this->cursor.GetLineNumber() - 1);
    int current_character_position = this->cursor.GetColumnNumber();

    if (current_character_position <= number_characters_in_prev_line) {
      this->cursor.MoveCursorUp();
    } else {
      this->cursor.MoveCursorToPosition(number_characters_in_prev_line, this->cursor.GetLineNumber() - 1);
    }
  }
}

void EditorContent::MoveCursorDown() {
  if (this->cursor.GetLineNumber() < this->text_document.GetNumberOfTotalLines() - 1) {
    int current_char_position = this->cursor.GetColumnNumber();
    int max_char_position_next_line = this->text_document.GetNumberOfCharactersInLine(this->cursor.GetLineNumber() + 1);

    if (current_char_position > max_char_position_next_line) {
      this->cursor.MoveCursorToPosition(max_char_position_next_line, this->cursor.GetLineNumber() + 1);
    } else {
      this->cursor.MoveCursorDown();
    }
  }
}

int EditorContent::GetNumberOfLines() const {
  return this->text_document.GetNumberOfTotalLines();
}

sf::String EditorContent::GetLineAt(int line_number) const {
  return text_document.GetLine(line_number);
}

void EditorContent::SetCursorAtPosition(int column_number, int line_number) {
  this->cursor.MoveCursorToPosition(column_number, line_number);
}

int EditorContent::GetNumberOfCharactersAtLine(int line_number) const {
  return this->text_document.GetNumberOfCharactersInLine(line_number);
}

void EditorContent::SetEditorCallbacks(EditorCallbacks *editor_callback) {
  this->callbacks = editor_callback;
}

void EditorContent::DeleteStringFromPosition(int position, int number_chars) {
  this->text_document.DeleteTextFromIndex(position, number_chars);
}

void EditorContent::InsertTextAtPosition(std::string &text, int position) {
  this->text_document.InsertTextAtIndex(text, position);
}
