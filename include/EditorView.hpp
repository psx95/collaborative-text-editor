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
  int font_size;
  float line_height;
  float char_width;

  sf::Color character_color;
  sf::View current_view;

  float ComputeCharacterWidth();
  void DrawCursor(sf::RenderWindow &render_window);
  void DrawTextAtLine(sf::RenderWindow &render_window, sf::String &text, int line_number);

 public:
  explicit EditorView(EditorContent &content, int view_width, int view_height);

  void Draw(sf::RenderWindow &render_window);
  void ScrollUp(sf::RenderWindow &render_window);
  void ScrollDown(sf::RenderWindow &render_window);
  void ScrollLeft(sf::RenderWindow &render_window);
  void ScrollRight(sf::RenderWindow &render_window);
  sf::View GetCurrentView() const;
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_EDITORVIEW_HPP_
