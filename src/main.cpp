#include <iostream>
#include <EditorWindow.hpp>

int main() {
  std::cout << "Hello, World!" << std::endl;
  EditorWindow window(sf::Color::Black);
  window.StartEventLoop();
  window.CloseWindow();
  return 0;
}
