//
// Created by psx95 on 11/16/20.
//

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include "EditorView.hpp"
#include "StringUtils.hpp"
EditorView::EditorView(EditorContent &editor_content, int width, int height) : content(editor_content) {
  if (!this->font.loadFromFile("fonts/DejaVuSansMono.ttf")) {
    exit(-1);
  }
  this->character_color = sf::Color::White;
  this->font_size = 16;
  this->char_width = ComputeCharacterWidth();
  this->line_height = font_size;
  this->current_view = sf::View(sf::FloatRect(0, 0, width, height));
}

void EditorView::ScrollUp(sf::RenderWindow &render_window) {
  // TODO : Update View
}

void EditorView::ScrollDown(sf::RenderWindow &render_window) {
  // TODO : Update View
}

void EditorView::ScrollLeft(sf::RenderWindow &render_window) {
  // TODO : Update View
}

void EditorView::ScrollRight(sf::RenderWindow &render_window) {
  // TODO : Update View
}

float EditorView::ComputeCharacterWidth() {
  sf::Text temp_text;
  temp_text.setFont(this->font);
  temp_text.setCharacterSize(this->font_size);
  temp_text.setString("_");
  return temp_text.getLocalBounds().width;
}
sf::View EditorView::GetCurrentView() const {
  return this->current_view;
}

void EditorView::Draw(sf::RenderWindow &render_window) {
  for (int line = 0; line < this->content.GetNumberOfLines(); line++) {
    sf::String current_line = this->content.GetLineAt(line);
    DrawTextAtLine(render_window, current_line, line);
  }
  DrawCursor(render_window);
  //std::cout << "text -> " << content.GetStringContent() << std::endl;
}

void EditorView::DrawTextAtLine(sf::RenderWindow &render_window, sf::String &text, int line_number) {
  sf::Text text_draw;
  text_draw.setFillColor(this->character_color);
  text_draw.setFont(font);
  text_draw.setString(text);
  text_draw.setCharacterSize(font_size);
  text_draw.setPosition(0, (float) line_number * line_height);
  render_window.draw(text_draw);
}

void EditorView::DrawCursor(sf::RenderWindow &window) {
  float y_offset = 2;
  float cursor_width = 2;
  std::pair<int, int> cursor_position = content.GetCursor().GetCurrentPosition();
  float cursor_column = cursor_position.first;
  float cursor_row = cursor_position.second;
  sf::RectangleShape cursor_shape(sf::Vector2f(cursor_width, this->line_height));
  cursor_shape.setFillColor(character_color);
  cursor_shape.setPosition(cursor_column * char_width, cursor_row * line_height + y_offset);
  window.draw(cursor_shape);
}