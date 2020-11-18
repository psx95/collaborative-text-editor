//
// Created by psx95 on 11/16/20.
//

#include <iostream>
#include "InputHandler.hpp"
InputHandler::InputHandler(EditorContent &_editor_content) : editor_content(_editor_content) {

}

void InputHandler::HandleEvents(EditorView &editor_view, sf::RenderWindow &render_window, sf::Event event) {
  HandleKeyboardEvents(editor_view, render_window, event);
  HandleMouseEvents(editor_view, render_window, event);
}

void InputHandler::HandleMouseEvents(EditorView &editor_view, sf::RenderWindow &render_window, sf::Event event) {
}

void InputHandler::HandleKeyboardEvents(EditorView &editor_view, sf::RenderWindow &render_window, sf::Event event) {
  //std::cout << "Event type is " << event.type << std::endl;
  if (event.type == sf::Event::TextEntered) {
    if (event.text.unicode == 8 || event.text.unicode == 127) {
      // filter out backspace and delete and treat them similarly
      editor_content.DeleteCharacterFromCursorPosition();
    } else if (event.text.unicode >= 32 || event.text.unicode == 13) {
      // handle only ascii characters
      editor_content.InsertCharacterAtCursor(static_cast<char>(event.text.unicode));
    }
  }
}
