//
// Created by psx95 on 11/16/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_EDITORCONTENT_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_EDITORCONTENT_HPP_

#include "Cursor.hpp"
#include "TextFileContent.hpp"
class EditorContent {
 private:
  // Text content
  Cursor cursor;
  TextFileContent &text_document;

 public:
  explicit EditorContent(TextFileContent &text_document);

  Cursor GetCursor();
  void InsertStringAtCursor(sf::String txt);
  void DeleteCharacterFromCursorPosition(int number_of_characters);
  int GetNumberOfLines() const;
  sf::String GetLineAt(int line_number) const;

  void MoveCursorRight();
  void MoveCursorLeft();
  void MoveCursorUp();
  void MoveCursorDown();


  std::string GetStringContent();
  std::vector<int> &GetLinePositions();

};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_EDITORCONTENT_HPP_
