//
// Created by psx95 on 11/26/20.
//

#include "CustomMessageException.hpp"

#include <utility>

CustomMessageException::CustomMessageException(std::string message) : message(std::move(message)) {
}