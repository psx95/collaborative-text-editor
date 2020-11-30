cmake_minimum_required(VERSION 3.10)
project(collaborative_text_editor)

set(CMAKE_CXX_STANDARD 11)

# source files in the project
SET(SOURCE src/editor/EditorWindow.cpp src/editor/Cursor.cpp src/editor/EditorContent.cpp src/editor/EditorView.cpp src/editor/InputHandler.cpp src/editor/TextFileContent.cpp src/ApplicationController.cpp src/editor/EditorCallbacks.cpp src/exceptions/CustomMessageException.cpp src/crdt/CRDTManager.cpp src/networking/UDPClient.cpp src/networking/NetworkingCallbacks.cpp src/version_vector/VersionVector.cpp src/crdt/CRDTCharacter.cpp)
# header files in the project, third party headers not included
SET(HEADERS include/EditorWindow.hpp include/Cursor.hpp include/EditorContent.hpp include/EditorView.hpp include/InputHandler.hpp include/StringUtils.hpp include/TextFileContent.hpp include/ApplicationController.hpp include/EditorCallbacks.hpp include/CustomMessageException.hpp include/CRDTManager.hpp include/CommonStructs.hpp include/NetworkingCallbacks.hpp include/UDPClient.hpp include/VersionVector.hpp include/CRDTCharacter.hpp)
# test source files in the project
SET(TEST_SOURCE tst/crdt_action_test.cpp)

#Providing location of include directories containing header files
include_directories("usr/include/")
include_directories("./include/")

#Providing location of 3rd Party libraries used in the project
link_directories("/usr/lib/x86_64-linux-gnu/")

message(STATUS ${CMAKE_SYSTEM_NAME})
message(STATUS "BUILDING FOR ${CMAKE_SYSTEM}")
#Configuration for the generated files
add_executable(collaborative_text_editor ${HEADERS} ${SOURCE} ./src/main.cpp)
add_executable(collaborative_text_editor_test ${SOURCE} ${TEST_SOURCE})

#Providing the specific libraries to use. This line needs to come after adding executables
target_link_libraries(collaborative_text_editor sfml-graphics sfml-window sfml-system sfml-network GL pthread)
target_link_libraries(collaborative_text_editor_test sfml-graphics sfml-window sfml-system sfml-network GL pthread)
