//
// Created by psx95 on 11/26/20.
//

#include <iostream>
#include "ApplicationController.hpp"
ApplicationController::ApplicationController(EditorWindow &editor, CRDTManager &crdt, UDPClient &client)
    : editor_window(editor), crdt_manager(crdt), udp_client(client) {
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
  std::cout << "Editor Callback: local insert " << text.toAnsiString() << " at " << index << std::endl;
}

void ApplicationController::OnLocalDelete(int index) {
  std::cout << "Editor Callback: local delete from position " << index << std::endl;
}

void ApplicationController::OnRemoteInsertReceive(sf::Packet &packet) {
  std::cout << "Networking Callback: remote insert packet received of size " << packet.getDataSize() << std::endl;
}

void ApplicationController::OnRemoteDeleteReceive(sf::Packet &packet) {
  std::cout << "Networking Callback: remote delete packet received of size " << packet.getDataSize() << std::endl;
}
