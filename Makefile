CC = g++ -std=gnu++0x -std=c++17

MAIN_ALGO_FILE = main.cpp
MAIN_BIN_FILE = main_bin.exe

SOURCE_DIRNAME = source
UTILS_DIR := $(SOURCE_DIRNAME)/utils
SUFFIX_FOREST_DIR := $(SOURCE_DIRNAME)/suffix_forest

TEST_DIRNAME = tests
SUFFIX_FOREST_TESTS_DIR := $(TEST_DIRNAME)/suffix_forest

UTILS_FILES := $(shell find ./$(UTILS_DIR) -name "*.cpp")
SUFFIX_TREE_SOURCE_FILES := $(shell find ./$(SUFFIX_FOREST_DIR) -name "*.cpp")

ALL_SOURCE_FILES := $(shell find ./$(SOURCE_DIRNAME) -name "*.cpp")
ALL_HEADERS_FILES := $(shell find ./$(SOURCE_DIRNAME) -name "*.hpp")

SUFFIX_TREE_TESTS := $(addprefix $(SUFFIX_FOREST_TESTS_DIR)/, $(addsuffix .exe, \
	$(shell find ./$(SUFFIX_FOREST_TESTS_DIR) -iname "*.cpp" -execdir basename {} .cpp ';')))


all: suffix_forest_tests main

$(MAIN_BIN_FILE) : $(ALL_SOURCE_FILES) $(ALL_HEADERS_FILES)
	@$(CC) $^ -o $@

$(SUFFIX_FOREST_TESTS_DIR)/%.exe : $(SUFFIX_FOREST_TESTS_DIR)/%.cpp $(SUFFIX_TREE_SOURCE_FILES)
	@$(CC) $^ -o $@

main : $(MAIN_BIN_FILE)
	@./$^

suffix_forest_tests: $(SUFFIX_TREE_TESTS)
	$(addsuffix $() &&, $(addprefix ./, $(SUFFIX_TREE_TESTS))) echo "Finished tests";

clean:
	@rm $(SUFFIX_FOREST_TESTS_DIR)/*.exe $(MAIN_BIN_FILE)
