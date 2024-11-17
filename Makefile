SRC_DIR = src
BUILD_DIR = build/debug
TEST_DIR = tests
TEST_BUILD_DIR = build/tests
CC = g++
SRC_FILES = $(wildcard $(SRC_DIR)/cpu/*.cpp) $(wildcard $(SRC_DIR)/memory/*.cpp)
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)
OBJ_NAME = legendarytrain
TEST_OBJ_NAME = test_legendarytrain
LIBRARY_PATHS = -lSDL2
COMPILER_FLAGS = -std=c++17
# COMPILER_FLAGS = -std=c++17 -Wall -O0 -g

all: 
	$(CC) $(COMPILER_FLAGS) $(LIBRARY_PATHS) $(SRC_DIR)/main.cpp $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)

test: 
	$(CC) $(COMPILER_FLAGS) $(LIBRARY_PATHS) $(SRC_FILES) $(TEST_FILES) -o $(TEST_BUILD_DIR)/$(TEST_OBJ_NAME)

run: 
	./$(BUILD_DIR)/$(OBJ_NAME)

testrun:
	./$(TEST_BUILD_DIR)/$(TEST_OBJ_NAME)

clean:
	rm -rf $(BUILD_DIR)/* $(TEST_BUILD_DIR)/*