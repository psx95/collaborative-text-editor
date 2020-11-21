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

void TextFileContent::AddTextAtPosition(sf::String &text, int line_number, int column_number) {
  int text_insert_position = GetStringPositionFromCursorPosition(line_number, column_number);
  this->string_content.insert(text_insert_position, text);

  int number_of_lines = this->line_positions.size();
  for (int i = line_number + 1; i < number_of_lines; i++) {
    this->line_positions[i] += text.getSize(); // update the new positions of '\n'
  }

  for (int i = 0; i < text.getSize(); i++) {
    if (text[i] == '\n' || text[i] == 13) {
      int new_line_start_position = text_insert_position + i + 1; // +1 because the new line will start after \n
      // insert the new line character to the line positions
      auto sorted_position =
          std::lower_bound(this->line_positions.begin(), this->line_positions.end(), new_line_start_position);
      this->line_positions.insert(sorted_position, new_line_start_position);
    }
  }
}

void TextFileContent::RemoveTextFromPosition(int amount, int line_number, int column_number) {

}

int TextFileContent::GetStringPositionFromCursorPosition(int line_number, int column_number) {
  if (line_number >= this->line_positions.size()) {
    std::cerr << " Unable to resolve Cursor Position to string position " << std::endl;
  }
  std::cout << "line position size " << line_positions.size() << std::endl;
  return this->line_positions.at(line_number) + column_number;
}

int TextFileContent::GetNumberOfCharactersInLine(int line_number) {
  if (line_number == this->line_positions.size() - 1) {
    // last line
    return (int) this->string_content.getSize() - this->line_positions.at(line_number);
  } else {
    return this->line_positions.at(line_number + 1) - this->line_positions.at(line_number) - 1;
  }
}

int TextFileContent::GetNumberOfTotalLines() const {
  return line_positions.size();
}
