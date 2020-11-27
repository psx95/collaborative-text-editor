//
// Created by psx95 on 11/27/20.
//

#include <CustomMessageException.hpp>
#include "NetworkingCallbacks.hpp"

void NetworkingCallbacks::OnRemoteOperationReceive(struct CRDTAction &crdt_action) {
  throw CustomMessageException("OnRemoteInsertReceive not implemented yet!");
}
