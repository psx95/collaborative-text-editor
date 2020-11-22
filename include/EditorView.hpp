//
// Created by psx95 on 11/16/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_EDITORVIEW_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_EDITORVIEW_HPP_

#include <SFML/Graphics/Font.hpp>
#include "EditorContent.hpp"

/*!
 * @brief This class represents the current view that is visible in the window.
 * @details The rendering of the view is managed by this class, the portion of the render visible to the user is also
 * set by this class.
 */
class EditorView {
 private:
  EditorContent &content; // the content that needs to be rendered inside the view
  sf::Font font; // the font options for the text
  int font_size; // the size of the font in which the text needs to be displayed
  float line_height; // the height of each line in the text
  float char_width; // the width of a single character in a particular font

  sf::Color character_color; // the current character color
  sf::View current_view; // the current view object that holds the rendered view

  float ComputeCharacterWidth(); // computes the width of the single character as perceived on the view
  void DrawCursor(sf::RenderWindow &render_window); // draws the cursor visual on screen
  // draws text at a given line number
  void DrawTextAtLine(sf::RenderWindow &render_window, sf::String &text, int line_number);

 public:
  /*!
   * @brief The public constructor for the EditorView.
   * @param content The content that should be rendered inside the current view.
   * @param view_width The width of the view in pixels.
   * @param view_height The height of the view in pixels.
   */
  explicit EditorView(EditorContent &content, int view_width, int view_height);

  /*!
   * @brief This method is responsible for drawing/rendering the content on the screen.
   * @param render_window The GUI window on which the view will be rendered.
   */
  void Draw(sf::RenderWindow &render_window);
  void ScrollUp(sf::RenderWindow &render_window);
  void ScrollDown(sf::RenderWindow &render_window);
  void ScrollLeft(sf::RenderWindow &render_window);
  void ScrollRight(sf::RenderWindow &render_window);

  /*!
   * @brief Getter function for the currently configured view object.
   * @return The current view object.
   */
  sf::View GetCurrentView() const;
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_EDITORVIEW_HPP_
