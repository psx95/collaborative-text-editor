//
// Created by psx95 on 11/26/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_APPLICATIONCONTROLLER_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_APPLICATIONCONTROLLER_HPP_

#include "EditorWindow.hpp"
#include "CRDTManager.hpp"
#include "NetworkingCallbacks.hpp"
#include "UDPClient.hpp"
#include "VersionVector.hpp"

class ApplicationController : public EditorCallbacks, public NetworkingCallbacks {
 private:
  EditorWindow &editor_window;
  CRDTManager &crdt_manager;
  UDPClient &udp_client;
  VersionVector &version_vector;

  void Init();

  void OnRemoteInsertReceive(struct CRDTAction &crdt_action);

  void OnRemoteDeleteReceive(struct CRDTAction &crdt_action);

 public:
  explicit ApplicationController(EditorWindow &editor, CRDTManager &crdt, UDPClient &client, VersionVector &vector);

  void Go();

  void Shutdown();

  void OnLocalInsert(sf::String &text, int index) override;

  void OnLocalDelete(int index) override;

  void OnRemoteOperationReceive(struct CRDTAction &crdt_action) override;
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_APPLICATIONCONTROLLER_HPP_
