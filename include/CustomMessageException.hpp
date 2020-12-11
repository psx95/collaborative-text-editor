//
// Created by psx95 on 11/26/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_EXCEPTION_CUSTOMMESSAGEEXCEPTION_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_EXCEPTION_CUSTOMMESSAGEEXCEPTION_HPP_

#include <string>
/*!
 * @brief This class represents a custom exception that is thrown with a message defined by the user.
 */
class CustomMessageException : public std::exception {
 private:
  const std::string message; // the message string explaining the exception
  CustomMessageException() = default;

 public:
  /*!
   * @brief Public constructor for the CustomMessageException.
   * @param message The exception message explaining the message & any additional details.
   */
  explicit CustomMessageException(std::string message);
  const char *what() const noexcept override {
    return message.c_str();
  }
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_EXCEPTION_CUSTOMMESSAGEEXCEPTION_HPP_
