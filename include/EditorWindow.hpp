//
// Created by psx95 on 11/15/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_EDITORWINDOW_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_EDITORWINDOW_HPP_
#include <SFML/Graphics.hpp>

class EditorWindow {
 private:
  sf::RenderWindow *editor_window{};
  sf::Color background_color{};

  void InitializeEditorWindow();
  void UpdateEvents();
  void DrawUpdates();

 public:
  explicit EditorWindow(sf::Color background_color);

  void StartEventLoop();

  void CloseWindow();

  ~EditorWindow();
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_EDITORWINDOW_HPP_
