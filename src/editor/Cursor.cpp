//
// Created by psx95 on 11/16/20.
//

#include "Cursor.hpp"

Cursor::Cursor() {
  this->line_number = 0;
  this->column_number = 0;
  this->max_column_number = 0;
  this->max_line_number = 0;
}

void Cursor::UpdateCursorPosition(int _column_number, int _line_number) {
  this->column_number = _column_number;
  this->line_number = _line_number;
}

void Cursor::MoveCursorUp() {
  if (line_number <= 0) {
    return;
  }
  UpdateCursorPosition(this->column_number, this->line_number - 1);
}

void Cursor::MoveCursorDown() {
  if (line_number >= max_line_number) {
    return;
  }
  UpdateCursorPosition(this->column_number, this->line_number + 1);
}

void Cursor::MoveCursorLeft() {
  if (column_number <= 0) {
    return;
  }
  UpdateCursorPosition(this->column_number - 1, this->line_number);
}

void Cursor::MoveCursorRight(bool insert_char) {
  if (!insert_char && column_number >= max_column_number) {
    return;
  }
  this->max_column_number += 1;
  UpdateCursorPosition(this->column_number + 1, this->line_number);
}

void Cursor::UpdateMaxLineNumber(int updated_max_line_number) {
  this->max_line_number = updated_max_line_number;
}

void Cursor::UpdateMaxColumnNumber(int updated_max_column_number) {
  this->max_column_number = updated_max_column_number;
}

std::pair<int, int> Cursor::GetCurrentPosition() {
  return {this->column_number, this->line_number};
}

void Cursor::MoveCursorToPosition(int _column_number, int _line_number) {
  this->line_number = _line_number;
  this->column_number = _column_number;
}
