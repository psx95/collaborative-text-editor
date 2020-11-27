//
// Created by psx95 on 11/27/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_NETWORKING_NETWORKINGCALLBACKS_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_NETWORKING_NETWORKINGCALLBACKS_HPP_

/*!
 * @brief This class acts like interface callbacks for the UDPClient. This interface will allow implementing classes
 * to know of certain events that occur in the UDPClient.
 */
class NetworkingCallbacks {
 public:
  /*!
   * @brief This method notifies implementing classes about an event that occurs at another connected peer.
   * @details The implementation for this method should contain code that runs whenever a remote event occurs.
   * @param crdt_action The CRDTAction object that contains the details about the remote action.
   */
  virtual void OnRemoteOperationReceive(struct CRDTAction &crdt_action);
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_NETWORKING_NETWORKINGCALLBACKS_HPP_
