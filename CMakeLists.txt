cmake_minimum_required(VERSION 3.10)
project(collaborative_text_editor)

set(CMAKE_CXX_STANDARD 11)

# source files in the project
SET(SOURCE)
# header files in the project, third party headers not included
SET(HEADERS)

#Providing location of include directories containing header files
include_directories("usr/include/")
include_directories("./include/")

#Providing location of 3rd Party libraries used in the project
#link_directories("/usr/lib/x86_64-linux-gnu/")

message(STATUS ${CMAKE_SYSTEM_NAME})
message(STATUS "BUILDING FOR ${CMAKE_SYSTEM}")
#Configuration for the generated files
add_executable(collaborative_text_editor ${SOURCE} ./src/main.cpp)

#Providing the specific libraries to use. This line needs to come after adding executables
target_link_libraries(collaborative_text_editor ncurses pthread)