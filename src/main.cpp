#include <iostream>
#include <EditorWindow.hpp>
#include <ApplicationController.hpp>

int main() {
  std::cout << "Starting Application" << std::endl;
  EditorWindow window(sf::Color(47, 50, 47));
  ApplicationController controller(window);
  controller.Go();
  controller.Shutdown();
  return 0;
}
