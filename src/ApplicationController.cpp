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
  for (int position : insert_action.Positions()) {
    std::cout << position << ",";
  }
  std::cout << std::endl;
  std::cout << "Editor Callback: local insert " << text.toAnsiString() << " at " << index << std::endl;
  udp_client.BroadcastActionToAllConnectedPeers(insert_action,
                                                crdt_manager.GetSiteId(),
                                                version_vector.GetSiteCounter());
}

void ApplicationController::OnLocalDelete(int index) {
  version_vector.IncrementSiteCounter();
  struct CRDTAction
      delete_action = crdt_manager.GenerateCRDTActionForLocalDelete(index, version_vector.GetSiteCounter());
  std::cout << "Editor Callback: local delete from position " << index << std::endl;
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
    if (crdt_action.Operation() == INSERT) {
      ApplicationController::OnRemoteInsertReceive(crdt_action, sender_site_id, sender_site_counter);
    } else if (crdt_action.Operation() == DELETE) {
      ApplicationController::OnRemoteDeleteReceive(crdt_action, sender_site_id, sender_site_counter);
    } else {
      // Dont want to throw exception since it will exit the program, ideally we would nopt want app to crash just because
      // of a single packet.
      std::cerr << "Unrecognized action received " << crdt_action.Operation() << std::endl;
    }
  }
}

void ApplicationController::OnRemoteInsertReceive(struct CRDTAction &crdt_action,
                                                  std::string &sender_site_id,
                                                  int sender_site_counter) {
  std::cout << "Networking Callback: remote insert packet received from client " << sender_site_id << std::endl;
  std::pair<std::string, int> insert_info = crdt_manager.GenerateStringInsertInfoFromRemoteInsert(crdt_action);
  std::cout << "[Remote] Inserting at local index " << insert_info.second << ", " << insert_info.first << std::endl;
  editor_window.InsertText(insert_info.first, insert_info.second);
}

void ApplicationController::OnRemoteDeleteReceive(struct CRDTAction &crdt_action,
                                                  std::string &sender_site_id,
                                                  int sender_site_counter) {
  std::cout << "Networking Callback: remote delete packet received from client " << sender_site_id << std::endl;
  int index = crdt_manager.GenerateDeleteInfoFromRemoteDelete(crdt_action);
  std::cout << "[Remote] Deleting from local index " << index << std::endl;
  if (index >= 0) {
    editor_window.DeleteTextFrom(index);
  }
}
