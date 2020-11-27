//
// Created by tsnaik on 11/27/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SHAREDSTRUCTS_HPP
#define COLLABORATIVE_TEXT_EDITOR_SHAREDSTRUCTS_HPP

#include <string>
#include <vector>

using namespace std;

struct CRDTAction {
    string actionType; // "insert" or "delete"
    string siteId; // unique id of the client
    int counter; // site counter managed by version vector
    char value; // value of the character to be inserted/deleted
    vector<int> position; // fractional position calculated by CRDT
};

#endif //COLLABORATIVE_TEXT_EDITOR_SHAREDSTRUCTS_HPP
