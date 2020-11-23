#include <iostream>
#include <EditorWindow.hpp>

int main() {
  std::cout << "Hello, World!" << std::endl;
  EditorWindow window(sf::Color(47, 50, 47));
  window.StartEventLoop();
  window.CloseWindow();
  return 0;
}
