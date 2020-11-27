#include <iostream>
#include <EditorWindow.hpp>
#include <ApplicationController.hpp>
#include <CRDTManager.hpp>

int main() {
  std::cout << "Starting Application" << std::endl;
  EditorWindow window(sf::Color(47, 50, 47));
  CRDTManager crdt_manager(0);
  ApplicationController controller(window, crdt_manager);
  controller.Go();
  controller.Shutdown();
  return 0;
}
