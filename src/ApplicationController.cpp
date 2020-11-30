//
// Created by psx95 on 11/26/20.
//

#include <iostream>
#include "ApplicationController.hpp"
ApplicationController::ApplicationController(EditorWindow &editor,
                                             CRDTManager &crdt,
                                             UDPClient &client,
                                             VersionVector &vector)
    : editor_window(editor), crdt_manager(crdt), udp_client(client), version_vector(vector) {
  Init();
}

void ApplicationController::Init() {
  editor_window.SetEditorCallbacks(this);
  udp_client.SetClientCallbacks(this);
}

void ApplicationController::Go() {
  editor_window.StartEventLoop();
}

void ApplicationController::Shutdown() {
  editor_window.CloseWindow();
}

void ApplicationController::OnLocalInsert(sf::String &text, int index) {
  version_vector.IncrementSiteCounter();
  struct CRDTAction
      action = crdt_manager.GenerateCRDTActionForLocalInsert(text[0], index, version_vector.GetSiteCounter());
  for (int position : action.Positions()) {
    std::cout << position << ",";
  }
  std::cout << std::endl;
  std::cout << "Editor Callback: local insert " << text.toAnsiString() << " at " << index << std::endl;
}

void ApplicationController::OnLocalDelete(int index) {
  std::cout << "Editor Callback: local delete from position " << index << std::endl;
}

void ApplicationController::OnRemoteOperationReceive(struct CRDTAction &crdt_action) {
  // check action and handle insert or delete
}

void ApplicationController::OnRemoteInsertReceive(struct CRDTAction &crdt_action) {
  std::cout << "Networking Callback: remote insert packet received from client " << crdt_action.SiteId() << std::endl;
}

void ApplicationController::OnRemoteDeleteReceive(struct CRDTAction &crdt_action) {
  std::cout << "Networking Callback: remote delete packet received from client " << crdt_action.SiteId() << std::endl;
}
