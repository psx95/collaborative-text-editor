//
// Created by psx95 on 11/26/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_APPLICATIONCONTROLLER_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_APPLICATIONCONTROLLER_HPP_

#include "EditorWindow.hpp"
#include "CRDTManager.hpp"

class ApplicationController : public EditorCallbacks {
 private:
  EditorWindow &editor_window;
  CRDTManager &crdt_manager;

  void Init();

 public:
  explicit ApplicationController(EditorWindow &editor, CRDTManager &crdt);

  void Go();

  void Shutdown();

  void OnLocalInsert(sf::String &text, int index) override;

  void OnLocalDelete(int index) override;
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_APPLICATIONCONTROLLER_HPP_
