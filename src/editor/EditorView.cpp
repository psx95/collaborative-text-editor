//
// Created by psx95 on 11/16/20.
//

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "EditorView.hpp"
EditorView::EditorView(EditorContent &editor_content, int width, int height) : content(editor_content) {
  if (!this->font.loadFromFile("fonts/DejaVuSansMono.ttf")) {
    exit(-1);
  }
  this->character_color = sf::Color::White;
  this->charWidth = ComputeCharacterWidth(16);
  this->lineHeight = 16;
  this->current_view = sf::View(sf::FloatRect(0, 0, width, height));
}

void EditorView::DrawCursor(sf::RenderWindow &window) {
  float y_offset = 2;
  float cursor_width = 2;
  std::pair<int, int> cursor_position = content.GetCursor().GetCurrentPosition();
  float cursor_column = cursor_position.first;
  float cursor_row = cursor_position.second;
  sf::RectangleShape cursor_shape(sf::Vector2f(cursor_width, this->lineHeight));
  cursor_shape.setFillColor(character_color);
  cursor_shape.setPosition(cursor_column * charWidth, cursor_row * lineHeight + y_offset);
  window.draw(cursor_shape);
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

float EditorView::ComputeCharacterWidth(int intended_size) {
  sf::Text temp_text;
  temp_text.setFont(this->font);
  temp_text.setCharacterSize(intended_size);
  temp_text.setString("a");
  return temp_text.getLocalBounds().width;
}
sf::View EditorView::GetCurrentView() const {
  return this->current_view;
}
