//
// Created by psx95 on 11/16/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_INPUTHANDLER_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_INPUTHANDLER_HPP_

#include "EditorContent.hpp"
#include "EditorView.hpp"
#include <SFML/Window/Event.hpp>

class InputHandler {
 private:
  EditorContent &editor_content;
  void HandleMouseEvents(EditorView &editor_view, sf::RenderWindow &render_window, sf::Event event);
  void HandleKeyboardEvents(EditorView &editor_view, sf::RenderWindow &render_window, sf::Event event);
  void HandleTextEntryEvents(EditorView &editor_view, sf::RenderWindow &render_window, sf::Event event);
  void HandleOtherKeyboardEvents(EditorView &editor_view, sf::RenderWindow &render_window, sf::Event event);

 public:
  explicit InputHandler(EditorContent &_editor_content);
  void HandleEvents(EditorView &editor_view, sf::RenderWindow &render_window, sf::Event event);
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_INPUTHANDLER_HPP_
