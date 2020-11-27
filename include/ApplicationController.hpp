//
// Created by psx95 on 11/26/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_APPLICATIONCONTROLLER_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_APPLICATIONCONTROLLER_HPP_

#include "EditorWindow.hpp"
#include "CRDTManager.hpp"
#include "NetworkingCallbacks.hpp"
#include "UDPClient.hpp"

class ApplicationController : public EditorCallbacks, public NetworkingCallbacks {
 private:
  EditorWindow &editor_window;
  CRDTManager &crdt_manager;
  UDPClient &udp_client;

  void Init();

 public:
  explicit ApplicationController(EditorWindow &editor, CRDTManager &crdt, UDPClient &client);

  void Go();

  void Shutdown();

  void OnLocalInsert(sf::String &text, int index) override;

  void OnLocalDelete(int index) override;

  void OnRemoteInsertReceive(sf::Packet &packet) override;

  void OnRemoteDeleteReceive(sf::Packet &packet) override;
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_APPLICATIONCONTROLLER_HPP_
