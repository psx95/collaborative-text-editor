//
// Created by psx95 on 11/15/20.
//

#include <iostream>
#include "EditorWindow.hpp"
EditorWindow::EditorWindow(sf::Color background_color) {
  InitializeEditorWindow();
  this->background_color = background_color;
}

void EditorWindow::InitializeEditorWindow() {
  editor_window = new sf::RenderWindow(sf::VideoMode(1080, 720), "Co-Text", sf::Style::Default);
  editor_window->setVerticalSyncEnabled(true);
  editor_window->clear(background_color);
}

void EditorWindow::StartEventLoop() {
  while (editor_window != nullptr && editor_window->isOpen()) {
    UpdateEvents(); // poll for events
    DrawUpdates(); // render text
  }
}

void EditorWindow::UpdateEvents() {
  sf::Event event{};
  while (editor_window->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      CloseWindow();
      break;
    }
    std::cout << "Event is " << event.type << std::endl;
  }
}

void EditorWindow::DrawUpdates() {
  editor_window->clear(background_color);
  // update window view
  editor_window->display();
}

void EditorWindow::CloseWindow() {
  if (editor_window != nullptr && editor_window->isOpen()) {
    editor_window->close();
  }
}

EditorWindow::~EditorWindow() {
  delete editor_window;
}
