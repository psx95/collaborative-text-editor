//
// Created by psx95 on 11/26/20.
//

#include "CustomMessageException.hpp"

CustomMessageException::CustomMessageException(const std::string &message) {
  CustomMessageException::message = &message;
}

const char *CustomMessageException::what() const noexcept {
  return message->c_str();
}
