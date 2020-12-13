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
      insert_action = crdt_manager.GenerateCRDTActionForLocalInsert(text[0], index, version_vector.GetSiteCounter());

  std::cout << "[Local]  [Insert] " << index << ":" << text.toAnsiString() << std::endl;

  udp_client.BroadcastActionToAllConnectedPeers(insert_action,
                                                crdt_manager.GetSiteId(),
                                                version_vector.GetSiteCounter());
}

void ApplicationController::OnLocalDelete(int index) {
  if (index < 0 || index >= crdt_manager.GetCRDTCharacters()->size()) {
    std::cerr << "Invalid Index " << index << " for local delete " << std::endl;
    return;
  }
  version_vector.IncrementSiteCounter();
  struct CRDTAction
      delete_action = crdt_manager.GenerateCRDTActionForLocalDelete(index, version_vector.GetSiteCounter());
  std::cout << "[Local]  [Delete] " << index << ":" << delete_action.Text() << std::endl;

  udp_client.BroadcastActionToAllConnectedPeers(delete_action,
                                                crdt_manager.GetSiteId(),
                                                version_vector.GetSiteCounter());
}

void ApplicationController::OnRemoteOperationReceive(struct CRDTAction &crdt_action,
                                                     std::string &sender_site_id,
                                                     int sender_site_counter) {
  std::vector<CRDTAction>
      actions = version_vector.ProcessRemoteAction(crdt_action, sender_site_id, sender_site_counter);
  for (CRDTAction action: actions) {
    // check action and handle insert or delete
    if (action.Operation() == INSERT) {
      ApplicationController::OnRemoteInsertReceive(action, sender_site_id, sender_site_counter);
    } else if (action.Operation() == DELETE) {
      ApplicationController::OnRemoteDeleteReceive(action, sender_site_id, sender_site_counter);
    } else {
      // Don't want to throw exception since it will exit the program, ideally we would not want app to crash just because
      // of a single packet.
      std::cerr << "Unrecognized action received " << action.Operation() << std::endl;
      return;
    }
    udp_client.BroadcastActionToAllConnectedPeers(action, sender_site_id, sender_site_counter);
  }
}

void ApplicationController::OnRemoteInsertReceive(struct CRDTAction &crdt_action,
                                                  std::string &sender_site_id,
                                                  int sender_site_counter) {

  std::pair<std::string, int> insert_info = crdt_manager.GenerateStringInsertInfoFromRemoteInsert(crdt_action);
  std::cout << "[Remote] [Insert] " << insert_info.second << ":" << insert_info.first << std::endl;

  editor_window.InsertText(insert_info.first, insert_info.second);
}

void ApplicationController::OnRemoteDeleteReceive(struct CRDTAction &crdt_action,
                                                  std::string &sender_site_id,
                                                  int sender_site_counter) {
  int index = crdt_manager.GenerateDeleteInfoFromRemoteDelete(crdt_action);
  std::cout << "[Remote] [Delete] " << index << ":" << crdt_action.Text() << std::endl;

  if (index >= 0) {
    editor_window.DeleteTextFrom(index);
  }
}
