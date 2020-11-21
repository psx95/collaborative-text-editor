//
// Created by psx95 on 11/20/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_TEXTFILE_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_TEXTFILE_HPP_

#include <SFML/System/String.hpp>
#include <vector>
class TextFileContent {
 private:
  sf::String string_content;
  std::vector<int> line_positions{};

  int GetStringPositionFromCursorPosition(int line_number, int column_number);

 public:
  explicit TextFileContent();
  sf::String GetLine(int line_number);
  int GetNumberOfTotalLines() const;
  int GetNumberOfCharactersInLine(int line_number);
  void AddTextAtPosition(sf::String &text, int line_number, int column_number);
  void RemoveTextFromPosition(int amount, int line_number, int column_number);
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_TEXTFILE_HPP_
