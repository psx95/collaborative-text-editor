CC = g++
CFLAGS := -Wall -std=c++11
LIBS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lGL -lpthread

INCLUDE=-I./include/

TARGET := collaborative_text_editor collaborative_text_editor_test

SOURCE := ./src/crdt/*.cpp ./src/editor/*.cpp ./src/exceptions/*.cpp ./src/networking/*.cpp ./src/version_vector/*.cpp src/ApplicationController.cpp
TEST_SOURCE := ./tst/*.cpp

all: $(TARGET)

collaborative_text_editor: ;$(CC) $(CFLAGS) $(SOURCE) ./src/main.cpp $(INCLUDE) -o collaborative_text_editor $(LIBS)

collaborative_text_editor_test: ;$(CC) $(CFLAGS) $(SOURCE) $(TEST_SOURCE) $(INCLUDE) -o collaborative_text_editor_test $(LIBS)

clean: ;rm -rf *.o collaborative_text_editor collaborative_text_editor_test
