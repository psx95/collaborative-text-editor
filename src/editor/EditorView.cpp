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
  this->character_color = sf::Color(223, 227, 230);
  this->font_size = 16;
  this->char_width = ComputeCharacterWidth();
  this->line_height = font_size;
  this->margin_line_number_x = 50;
  this->vertical_scroll_amount = 25;
  SetViewBounds(width, height);
}

void EditorView::ScrollUp(sf::RenderWindow &render_window) {
  float window_height = render_window.getView().getSize().y;
  auto current_view_position = this->current_view.getCenter();
  if (current_view_position.y - window_height / 2 > 0) {
    this->current_view.move(0, -this->vertical_scroll_amount);
  }
}

void EditorView::ScrollDown(sf::RenderWindow &render_window) {
  float window_height = render_window.getView().getSize().y;
  auto current_view_position = this->current_view.getCenter();
  float bottom_view_limit_px = (float) this->content.GetNumberOfLines() * line_height;
  if ((current_view_position.y + window_height / 2) < (bottom_view_limit_px + vertical_scroll_amount)) {
    this->current_view.move(0, this->vertical_scroll_amount);
  }
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
    DrawLineNumberBox(render_window, line);
    DrawTextAtLine(render_window, current_line, line);
  }
  DrawCursor(render_window);
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
  cursor_shape.setFillColor(sf::Color::White);
  cursor_shape.setPosition(cursor_column * char_width, cursor_row * line_height + y_offset);
  window.draw(cursor_shape);
}

std::pair<int, int> EditorView::ConvertScreenCoordsToTextCoords(float screen_x_pos, float screen_y_pos) {
  int computed_line_number = (int) (screen_y_pos / this->line_height);
  int computed_column_number = 0;

  int last_line_number = this->content.GetNumberOfLines() - 1;

  if (computed_line_number < 0) {
    computed_line_number = 0;
    computed_column_number = 0;
  } else if (computed_line_number > last_line_number) {
    computed_line_number = last_line_number;
    computed_column_number = this->content.GetNumberOfCharactersAtLine(computed_line_number);
  } else {
    computed_column_number = (int) (screen_x_pos / this->char_width); // will not work if tab characters are supported
    computed_column_number = std::max(0, computed_column_number);
    computed_column_number =
        std::min(computed_column_number, this->content.GetNumberOfCharactersAtLine(computed_line_number));
  }
  return std::pair<int, int>{computed_column_number, computed_line_number};
}

void EditorView::DrawLineNumberBox(sf::RenderWindow &render_window, int line_number) {
  sf::Text line_number_text;
  line_number_text.setFillColor(sf::Color::Red);
  line_number_text.setStyle(sf::Text::Bold);
  line_number_text.setFont(this->font);
  line_number_text.setString(std::to_string(line_number + 1));
  line_number_text.setCharacterSize(this->font_size - 1);
  line_number_text.setPosition(-this->margin_line_number_x, (float) (font_size * line_number));

  sf::RectangleShape margin_box(sf::Vector2f(this->margin_line_number_x - 5, font_size));
  margin_box.setFillColor(sf::Color(68, 72, 68));
  margin_box.setPosition(-this->margin_line_number_x, (float) (font_size * line_number));

  render_window.draw(margin_box);
  render_window.draw(line_number_text);
}

void EditorView::SetViewBounds(unsigned int width, unsigned int height) {
  this->current_view = sf::View(sf::FloatRect(-55, 0, width, height));
}
