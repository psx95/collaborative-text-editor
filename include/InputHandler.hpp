//
// Created by psx95 on 11/16/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_INPUTHANDLER_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_INPUTHANDLER_HPP_

#include "EditorContent.hpp"
#include "EditorView.hpp"
#include <SFML/Window/Event.hpp>

/*!
 * @brief This class is responsible for handling all inputs that are made by the user via mouse and keyboard.
 */
class InputHandler {
 private:
  EditorContent &editor_content; // The editor content
  // handling for mouse events
  void HandleMouseEvents(EditorView &editor_view, sf::RenderWindow &render_window, sf::Event event);
  // handling for keyboard events
  void HandleKeyboardEvents(EditorView &editor_view, sf::RenderWindow &render_window, sf::Event event);
  // handling keyboard events that result in text entry
  void HandleTextEntryEvents(EditorView &editor_view, sf::RenderWindow &render_window, sf::Event event);
  // handling supported keyboard events other than text entry
  void HandleOtherKeyboardEvents(EditorView &editor_view, sf::RenderWindow &render_window, sf::Event event);

 public:
  /*!
   * @brief The public constructor for the InputHandler class.
   * @param _editor_content The object that represents and allows manipulating the actual content on screen.
   */
  explicit InputHandler(EditorContent &_editor_content);

  /*!
   * @brief This method is responsible for handling the various input events made by the user appropriately.
   * @param editor_view The view object that displays the current view on the GUI window.
   * @param render_window The RenderWindow object that allows the view to be drawn on it.
   * @param event The event that was made by the user.
   */
  void HandleEvents(EditorView &editor_view, sf::RenderWindow &render_window, sf::Event event);
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_INPUTHANDLER_HPP_
