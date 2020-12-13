//
// Created by psx95 on 11/15/20.
//

#include <iostream>
#include <CustomMessageException.hpp>
#include "EditorWindow.hpp"
EditorWindow::EditorWindow(sf::Color background_color, std::string &site_id) {
  InitializeEditorWindow(site_id);
  this->background_color = background_color;
}

void EditorWindow::InitializeEditorWindow(std::string &site_id) {
  std::string title = "Co-Text Client: ";
  editor_window = new sf::RenderWindow(sf::VideoMode(1080, 720), title.append(site_id), sf::Style::Default);
  editor_window->setVerticalSyncEnabled(true);
  editor_window->clear(background_color);

  text_file_content = new TextFileContent();
  editor_content = new EditorContent(*text_file_content);
  editor_view = new EditorView(*editor_content, editor_window->getSize().x, editor_window->getSize().y);
  input_handler = new InputHandler(*editor_content);
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
    } else if (event.type == sf::Event::Resized) {
      editor_view->SetViewBounds(event.size.width, event.size.height);
    }
    input_handler->HandleEvents(*editor_view, *editor_window, event);
  }
}

void EditorWindow::DrawUpdates() {
  editor_window->clear(background_color);
  // update window view
  editor_window->setView(editor_view->GetCurrentView());
  editor_view->Draw(*editor_window);
  editor_window->display();
}

void EditorWindow::CloseWindow() {
  if (editor_window != nullptr && editor_window->isOpen()) {
    editor_window->close();
  }
}

void EditorWindow::SetEditorCallbacks(EditorCallbacks *editor_callbacks) {
  if (!editor_callbacks) {
    throw CustomMessageException("EditorCallbacks cannot be set as null!");
  }
  editor_content->SetEditorCallbacks(editor_callbacks);
}

void EditorWindow::InsertText(std::string &text, int index) {
  editor_content->InsertTextAtPosition(text, index);
}

void EditorWindow::DeleteTextFrom(int index, int num_chars) {
  editor_content->DeleteStringFromPosition(index, num_chars);
}

EditorWindow::~EditorWindow() {
  delete editor_window;
  delete editor_view;
  delete editor_content;
}
