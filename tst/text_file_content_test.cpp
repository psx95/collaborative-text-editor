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

TEST_CASE("Local Delete = Remote Delete single line") {
  TextFileContent text_file_content;
  sf::String txt = "Dummy String for test";
  InsertTextCharacterByCharacter(txt, text_file_content);
  REQUIRE(text_file_content.GetNumberOfTotalLines() == 1);
  REQUIRE(text_file_content.GetNumberOfCharactersInLine(0) == txt.getSize());
  REQUIRE(text_file_content.GetLine(0) == txt);

  // remote insert in another peer
  TextFileContent text_file_content_remote;
  RemoteInsertCharacterByCharacter(txt, text_file_content_remote);
  REQUIRE(text_file_content.GetNumberOfTotalLines() == text_file_content_remote.GetNumberOfTotalLines());
  REQUIRE(text_file_content.GetLine(0) == text_file_content_remote.GetLine(0));

  // Delete as a local op
  // deleting locally from row 0 column 0 is not possible
  int deleted_position = text_file_content.RemoveTextFromPosition(1, 0, 2); // should delete 'u'
  REQUIRE(deleted_position == 1);
  sf::String expected_txt = "Dmmy String for test";
  REQUIRE(text_file_content.GetNumberOfTotalLines() == 1);
  REQUIRE(text_file_content.GetNumberOfCharactersInLine(0) == expected_txt.getSize());
  std::cout << "deleted text is " << text_file_content.GetLine(0).toAnsiString() << std::endl;
  REQUIRE(text_file_content.GetLine(0) == expected_txt);

  // Delete as a remote op
  int remote_delete_start_index = text_file_content_remote.DeleteTextFromIndex(1, 1);
  REQUIRE(remote_delete_start_index == 1);
  REQUIRE(text_file_content_remote.GetNumberOfTotalLines() == text_file_content.GetNumberOfTotalLines());
  REQUIRE(text_file_content_remote.GetNumberOfCharactersInLine(0) == text_file_content.GetNumberOfCharactersInLine(0));
  REQUIRE(text_file_content_remote.GetLine(0) == text_file_content.GetLine(0));
}

TEST_CASE("Local Delete = Remote Delete multi-line") {
  TextFileContent text_file_content;
  sf::String txt = "Dummy String for \ntest";
  InsertTextCharacterByCharacter(txt, text_file_content);
  REQUIRE(text_file_content.GetNumberOfTotalLines() == 2);
  REQUIRE(text_file_content.GetNumberOfCharactersInLine(0) + text_file_content.GetNumberOfCharactersInLine(1)
              == txt.getSize() - 1);
  REQUIRE(text_file_content.GetLine(0) == txt.substring(0, txt.find("\n")));

  // remote insert in peer
  TextFileContent text_file_content_remote;
  RemoteInsertCharacterByCharacter(txt, text_file_content_remote);
  REQUIRE(text_file_content.GetNumberOfTotalLines() == text_file_content_remote.GetNumberOfTotalLines());
  std::cout << "text is  " << text_file_content_remote.GetLine(0).toAnsiString() << std::endl;
  std::cout << "text is  " << text_file_content_remote.GetLine(1).toAnsiString() << std::endl;
  REQUIRE(text_file_content.GetLine(0) == text_file_content_remote.GetLine(0));
  REQUIRE(text_file_content.GetLine(1) == text_file_content_remote.GetLine(1));

  // delete as a local op
  // new line character is stored at the start of the current line
  int deleted_position = text_file_content.RemoveTextFromPosition(1, 1, 1); // should delete 'u'
  REQUIRE(deleted_position == 18);
  sf::String expected_txt = "Dummy String for \nest";
  REQUIRE(text_file_content.GetNumberOfTotalLines() == 2);
  REQUIRE(text_file_content.GetNumberOfCharactersInLine(0) + text_file_content.GetNumberOfCharactersInLine(1)
              == expected_txt.getSize() - 1); // new line not included in character count
  std::cout << "deleted text is " << text_file_content.GetLine(0).toAnsiString() << std::endl;
  REQUIRE(text_file_content.GetLine(0) == expected_txt.substring(0, expected_txt.find("\n")));
  REQUIRE(text_file_content.GetLine(1) == expected_txt.substring(expected_txt.find("\n") + 1));

  // remote delete
  int remote_delete_start_index = text_file_content_remote.DeleteTextFromIndex(18, 1);
  REQUIRE(remote_delete_start_index == 18);
  REQUIRE(text_file_content_remote.GetNumberOfTotalLines() == text_file_content.GetNumberOfTotalLines());
  REQUIRE(text_file_content_remote.GetNumberOfCharactersInLine(0) == text_file_content.GetNumberOfCharactersInLine(0));
  REQUIRE(text_file_content_remote.GetLine(0) == text_file_content.GetLine(0));
  REQUIRE(text_file_content_remote.GetLine(1) == text_file_content.GetLine(1));
}