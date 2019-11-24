CC = c++
CCLAGS = -pedantic-errors -Wall -Wextra -Werror -std=c++11
LDFLAGS = -L/usr/lib -lstdc++ -lm -pthread
BUILD = ./build
SRC_DIR=./src
TEST_DIR=./tests
SERVER_DIR=./server
OBJ_DIR = $(BUILD)/objects
APP_DIR = $(BUILD)/apps
TARGET = cppdb
SERVER_TARGET = dbserver
INCLUDE = -I include/
SRCS := $(shell find $(SRC_DIR) $(TEST_DIR) -name *.cpp)
SERVER_SRCS := $(shell find $(SRC_DIR) $(SERVER_DIR) -name *.cpp)
OBJECTS = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)
SERVER_OBJECTS = $(SERVER_SRCS:%.cpp=$(OBJ_DIR)/%.o)


all: build $(APP_DIR)/$(TARGET)
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS)

server: build $(APP_DIR)/$(SERVER_TARGET)
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(SERVER_TARGET): $(SERVER_OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(SERVER_TARGET) $(SERVER_OBJECTS)


.PHONY: all build clean

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
