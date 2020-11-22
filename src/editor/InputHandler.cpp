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
  if (event.type == sf::Event::MouseButtonPressed) {
    sf::Vector2<int> mouse_position_raw = sf::Mouse::getPosition(render_window);
    sf::Vector2f mouse_position_window = render_window.mapPixelToCoords(mouse_position_raw);
    std::pair<int, int>
        cursor_position = editor_view.ConvertScreenCoordsToTextCoords(mouse_position_window.x, mouse_position_window.y);
    editor_content.SetCursorAtPosition(cursor_position.first, cursor_position.second);
  }
}

void InputHandler::HandleKeyboardEvents(EditorView &editor_view, sf::RenderWindow &render_window, sf::Event event) {
  //std::cout << "Event type is " << event.type << std::endl;
  if (event.type == sf::Event::TextEntered) {
    HandleTextEntryEvents(editor_view, render_window, event);
  } else if (event.type == sf::Event::KeyPressed) {
    HandleOtherKeyboardEvents(editor_view, render_window, event);
  }
}

void InputHandler::HandleTextEntryEvents(EditorView &editor_view, sf::RenderWindow &render_window, sf::Event event) {
  if (event.text.unicode == 8 || event.text.unicode == 127) {
    // filter out backspace and delete and treat them similarly
    editor_content.DeleteCharacterFromCursorPosition(1);
  } else if (event.text.unicode >= 32 || event.text.unicode == 13) {
    // handle only ascii characters
    editor_content.InsertStringAtCursor(sf::String(event.text.unicode));
  }
}

void InputHandler::HandleOtherKeyboardEvents(EditorView &editor_view,
                                             sf::RenderWindow &render_window,
                                             sf::Event event) {
  if (event.key.code == sf::Keyboard::Up) {
    editor_content.MoveCursorUp();
  } else if (event.key.code == sf::Keyboard::Left) {
    editor_content.MoveCursorLeft();
  } else if (event.key.code == sf::Keyboard::Right) {
    editor_content.MoveCursorRight();
  } else if (event.key.code == sf::Keyboard::Down) {
    editor_content.MoveCursorDown();
  }
}
