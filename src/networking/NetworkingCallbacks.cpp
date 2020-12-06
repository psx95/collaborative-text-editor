//
// Created by psx95 on 11/27/20.
//

#include <CustomMessageException.hpp>
#include "NetworkingCallbacks.hpp"

void NetworkingCallbacks::OnRemoteOperationReceive(struct CRDTAction &crdt_action,
                                                   std::string &sender_site_id,
                                                   int sender_site_counter) {
  throw CustomMessageException("OnRemoteInsertReceive not implemented yet!");
}
