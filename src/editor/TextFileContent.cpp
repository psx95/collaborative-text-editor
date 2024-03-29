//
// Created by psx95 on 11/20/20.
//

#include <iostream>
#include "TextFileContent.hpp"
TextFileContent::TextFileContent() {
  this->line_positions.clear();
  this->line_positions.push_back(0);

  this->string_content = "";
}

sf::String TextFileContent::GetLine(int line_number) {
  int last_line_number = (int) this->line_positions.size() - 1;
  if (line_number < 0 || line_number > last_line_number) {
    return "";
  }

  if (line_number == last_line_number) {
    return this->string_content.substring(this->line_positions.at(line_number));
  }
  int required_line_start = this->line_positions.at(line_number);
  int next_line_start = this->line_positions.at(line_number + 1);
  int length_of_required_line = next_line_start - required_line_start - 1;
  return this->string_content.substring(required_line_start, length_of_required_line);
}

int TextFileContent::AddTextAtPosition(sf::String &text, int line_number, int column_number) {
  int text_insert_position = GetStringPositionFromCursorPosition(line_number, column_number);
  if (text_insert_position == -1 || text_insert_position > this->string_content.getSize()) {
    return -1;
  }
  this->string_content.insert(text_insert_position, text);

  int number_of_lines = this->line_positions.size();
  // if there are more lines ahead of the current line position
  for (int i = line_number + 1; i < number_of_lines; i++) {
    this->line_positions[i] += text.getSize(); // update the new positions of '\n'
  }

  for (int i = 0; i < text.getSize(); i++) {
    if (text[i] == '\n' || text[i] == 13 || text[i] == 10) {
      int new_line_start_position = text_insert_position + i + 1; // +1 because the new line will start after \n
      // insert the new line character to the line positions
      // lower_bound will find a position between begin and end that is just less than new_line_start_position
      auto sorted_position =
          std::lower_bound(this->line_positions.begin(), this->line_positions.end(), new_line_start_position);
      this->line_positions.insert(sorted_position, new_line_start_position);
    }
  }
  return text_insert_position;
}

int TextFileContent::RemoveTextFromPosition(int amount, int line_number, int column_number) {
  int cursor_current_position = GetStringPositionFromCursorPosition(line_number, column_number);
  int text_delete_start_position = -1;
  if (cursor_current_position >= 0) {
    text_delete_start_position = std::max(0, cursor_current_position - amount);
    if (text_delete_start_position < string_content.getSize()) {
      this->string_content.erase(text_delete_start_position, amount);
    } else {
      text_delete_start_position = -1;
    }
  }
  // update line positions
  this->line_positions.clear();
  this->line_positions.push_back(0);
  for (int i = 0; i < this->string_content.getSize(); i++) {
    if (this->string_content[i] == '\n' || this->string_content[i] == 13 || this->string_content[i] == 10) {
      this->line_positions.push_back(i + 1); // line starts after \n
    }
  }
  return text_delete_start_position;
}

int TextFileContent::GetStringPositionFromCursorPosition(int line_number, int column_number) {
  if (line_number >= this->line_positions.size()) {
    std::cerr << " Unable to resolve Cursor Position to string position " << std::endl;
    return -1;
  }
  return this->line_positions.at(line_number) + column_number;
}

int TextFileContent::GetNumberOfCharactersInLine(int line_number) {
  if (line_number == this->line_positions.size() - 1) {
    // last line
    return (int) this->string_content.getSize() - this->line_positions.at(line_number);
  } else {
    int size = line_positions.size();
    return this->line_positions.at(line_number + 1) - this->line_positions.at(line_number) - 1;
  }
}

int TextFileContent::GetNumberOfTotalLines() const {
  return line_positions.size();
}

int TextFileContent::InsertTextAtIndex(const std::string &text, int index) {
  std::pair<int, int> cursor_position = GetCursorPositionFromStringPosition(index);
  sf::String txt = text;
  return TextFileContent::AddTextAtPosition(txt, cursor_position.first, cursor_position.second);
}

int TextFileContent::DeleteTextFromIndex(int index, int number_characters) {
  std::pair<int, int> cursor_position = GetCursorPositionFromStringPosition(index);
  // plus one because cursor will be placed ahead of the character
  return TextFileContent::RemoveTextFromPosition(number_characters, cursor_position.first, cursor_position.second + 1);
}

std::pair<int, int> TextFileContent::GetCursorPositionFromStringPosition(int position_in_string) {
  // find highest line number position which comes right after the position
  int line_number = 0;
  int new_line_index = 0;
  for (int i = 0; i < line_positions.size(); i++) {
    if (position_in_string >= line_positions.at(i)) {
      line_number = i;
      new_line_index = line_positions.at(i); // index stored at new line position
    } else {
      break;
    }
  }
  int column_number = position_in_string - new_line_index;
  return {line_number, column_number};
}
