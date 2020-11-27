//
// Created by psx95 on 11/26/20.
//

#include <iostream>
#include "ApplicationController.hpp"
ApplicationController::ApplicationController(EditorWindow &editor) : editor_window(editor) {
  Init();
}

void ApplicationController::Init() {
  editor_window.SetEditorCallbacks(this);
}

void ApplicationController::Go() {
  editor_window.StartEventLoop();
}

void ApplicationController::Shutdown() {
  editor_window.CloseWindow();
}

void ApplicationController::OnLocalInsert(sf::String &text, int index) {
  std::cout << "Editor Callback: local insert " << text.toAnsiString() << " at " << index << std::endl;
}

void ApplicationController::OnLocalDelete(int index) {
  std::cout << "Editor Callback: local delete from position " << index << std::endl;
}
