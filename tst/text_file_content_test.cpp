//
// Created by psx95 on 12/5/20.
//

#include "catch.hpp"
#include <iostream>

#include <TextFileContent.hpp>

void InsertTextCharacterByCharacter(sf::String &txt, TextFileContent &text_file_content) {
  int line_number = 0;
  int column_number = 0;
  for (int i = 0; i < txt.getSize(); i++) {
    sf::String character = txt.substring(i, 1);
    text_file_content.AddTextAtPosition(character, line_number, column_number);
    if (character[0] == '\n' || character[0] == 13 || character[0] == 10) {
      line_number++;
      column_number = 0;
    } else {
      column_number++;
    }
  }
}

void RemoteInsertCharacterByCharacter(sf::String &txt, TextFileContent &text_file_content) {
  for (int i = 0; i < txt.getSize(); i++) {
    sf::String character = txt.substring(i, 1);
    text_file_content.InsertTextAtIndex(txt.substring(i, 1), i);
  }
}

TEST_CASE("Insert into text file") {
  TextFileContent text_file_content;
  sf::String txt = "a";
  text_file_content.AddTextAtPosition(txt, 0, 0);
  REQUIRE(text_file_content.GetNumberOfCharactersInLine(0) == 1);
  REQUIRE(text_file_content.GetNumberOfTotalLines() == 1);
  REQUIRE(text_file_content.GetLine(0) == txt);

  text_file_content.InsertTextAtIndex(txt, 1);
  REQUIRE(text_file_content.GetNumberOfCharactersInLine(0) == 2);
  REQUIRE(text_file_content.GetNumberOfTotalLines() == 1);
  sf::String new_expected = "aa";
  REQUIRE(text_file_content.GetLine(0) == new_expected);
}

TEST_CASE("Insert NewLine character in text file") {
  TextFileContent text_file_content;
  sf::String txt = "Dummy String for \ntest";
  InsertTextCharacterByCharacter(txt, text_file_content);
  REQUIRE(text_file_content.GetNumberOfTotalLines() == 2);
  REQUIRE(text_file_content.GetNumberOfCharactersInLine(0) + text_file_content.GetNumberOfCharactersInLine(1)
              == txt.getSize() - 1);
  REQUIRE(text_file_content.GetLine(0) == txt.substring(0, txt.find("\n")));
}

TEST_CASE("Local insert = Remote insert with newlines") {
  TextFileContent text_file_content;
  sf::String txt = "Dummy String for \ntest";
  InsertTextCharacterByCharacter(txt, text_file_content);
  REQUIRE(text_file_content.GetNumberOfTotalLines() == 2);
  REQUIRE(text_file_content.GetNumberOfCharactersInLine(0) + text_file_content.GetNumberOfCharactersInLine(1)
              == txt.getSize() - 1);
  REQUIRE(text_file_content.GetLine(0) == txt.substring(0, txt.find("\n")));

  TextFileContent text_file_content_remote;
  RemoteInsertCharacterByCharacter(txt, text_file_content_remote);
  REQUIRE(text_file_content.GetNumberOfTotalLines() == text_file_content_remote.GetNumberOfTotalLines());
  std::cout << "text is  " << text_file_content_remote.GetLine(0).toAnsiString() << std::endl;
  std::cout << "text is  " << text_file_content_remote.GetLine(1).toAnsiString() << std::endl;
  REQUIRE(text_file_content.GetLine(0) == text_file_content_remote.GetLine(0));
  REQUIRE(text_file_content.GetLine(1) == text_file_content_remote.GetLine(1));
}

TEST_CASE("Remote insert position = local insert") {
  TextFileContent text_file_content_local;
  sf::String txt = "\n";
  TextFileContent text_file_content_remote;
  REQUIRE(text_file_content_remote.AddTextAtPosition(txt, 0, 0) == text_file_content_local.InsertTextAtIndex(txt, 0));
}

TEST_CASE("Local insert = Remote Insert single line") {
  TextFileContent text_file_content;
  sf::String txt = "Dummy String for test";
  InsertTextCharacterByCharacter(txt, text_file_content);
  REQUIRE(text_file_content.GetNumberOfTotalLines() == 1);
  REQUIRE(text_file_content.GetNumberOfCharactersInLine(0) == txt.getSize());
  REQUIRE(text_file_content.GetLine(0) == txt);

  TextFileContent text_file_content_remote;
  RemoteInsertCharacterByCharacter(txt, text_file_content_remote);
  REQUIRE(text_file_content.GetNumberOfTotalLines() == text_file_content_remote.GetNumberOfTotalLines());
  std::cout << "text is  " << text_file_content_remote.GetLine(0).toAnsiString() << std::endl;
  REQUIRE(text_file_content.GetLine(0) == text_file_content_remote.GetLine(0));
}