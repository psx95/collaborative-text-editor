//
// Created by psx95 on 11/26/20.
//

#include <SFML/System/String.hpp>
#include <CustomMessageException.hpp>
#include "EditorCallbacks.hpp"

void EditorCallbacks::OnLocalInsert(sf::String &text, int index) {
  throw CustomMessageException("OnLocalInsert not implemented yet");
}

void EditorCallbacks::OnLocalDelete(int index) {
  throw CustomMessageException("OnLocalDelete is not implemented yet.");
}
