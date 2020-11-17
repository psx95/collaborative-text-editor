//
// Created by psx95 on 11/16/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_EDITORVIEW_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_EDITORVIEW_HPP_

#include <SFML/Graphics/Font.hpp>
#include "EditorContent.hpp"
class EditorView {
 private:
  EditorContent &content;
  sf::Font font;
  float lineHeight;
  float charWidth;

  sf::Color character_color;
  sf::View current_view;

  float ComputeCharacterWidth(int fontSize);

 public:
  explicit EditorView(EditorContent &content, int view_width, int view_height);

  void DrawCursor(sf::RenderWindow &render_window);
  void ScrollUp(sf::RenderWindow &render_window);
  void ScrollDown(sf::RenderWindow &render_window);
  void ScrollLeft(sf::RenderWindow &render_window);
  void ScrollRight(sf::RenderWindow &render_window);
  sf::View GetCurrentView() const;
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_EDITORVIEW_HPP_
