CC = g++ -std=gnu++0x -std=c++17

MAIN_ALGO_FILE = $(SOURCE_DIR)/main.cpp
MAIN_BIN_FILE = main_algo.exe
TEST_DIR_EXE_FILES := $(shell find ./$(TEST_FIR)/* -name "*.exe")

SOURCE_DIR = source
TEST_DIR = tests

UTILS_DIR := $(SOURCE_DIR)/utils
SUFFIX_FOREST_DIR := $(SOURCE_DIR)/suffix_forest
SUFFIX_FOREST_TESTS_DIR := $(TEST_DIR)/suffix_forest

ALL_SOURCE_CPP_FILES := $(shell find ./$(SOURCE_DIR)/*/* -name "*.cpp")
ALL_SOURCE_HPP_FILES := $(shell find ./$(SOURCE_DIR) -name "*.hpp")

SUFFIX_TREE_TESTS := $(addprefix $(SUFFIX_FOREST_TESTS_DIR)/, $(addsuffix .exe, \
	$(shell find ./$(SUFFIX_FOREST_TESTS_DIR) -iname "*.cpp" -execdir basename {} .cpp ';')))


all: suffix_forest_tests main

all_tests: suffix_forest_tests

suffix_forest_tests: $(SUFFIX_TREE_TESTS)
	@$(addsuffix $() &&, $(addprefix ./, $(SUFFIX_TREE_TESTS))) echo "Finished $@ tests";

main : $(MAIN_BIN_FILE)
	@./$^

$(SUFFIX_FOREST_TESTS_DIR)/%.exe : $(SUFFIX_FOREST_TESTS_DIR)/%.cpp $(ALL_SOURCE_CPP_FILES)
	@$(CC) $^ -o $@

$(MAIN_BIN_FILE) : $(MAIN_ALGO_FILE) $(ALL_SOURCE_CPP_FILES) $(ALL_SOURCE_HPP_FILES)
	@$(CC) $^ -o $@

clean:
	@rm $(TEST_DIR_EXE_FILES) $(MAIN_BIN_FILE)
