CC = g++ -std=gnu++0x

MAIN_ALGO_FILE = main.cpp
MAIN_BIN_FILE = main_bin.exe

SOURCE_DIRNAME = source
TEST_DIRNAME = tests
SUFFIX_TREE_TESTS_DIR := $(TEST_DIRNAME)/suffix_tree

UTILS_FILES = $(shell find ./$(SOURCE_DIRNAME)/utils -name "*.cpp")
SUFFIX_TREE_SOURCE_FILES = $(shell find ./$(SOURCE_DIRNAME)/suffix_tree -name "*.cpp")

ALL_SOURCE_FILES := $(shell find ./$(SOURCE_DIRNAME) -name "*.cpp")

SUFFIX_TREE_TESTS := $(addprefix $(SUFFIX_TREE_TESTS_DIR)/, \
	$(addsuffix .exe, \
		$(shell find ./$(SUFFIX_TREE_TESTS_DIR) -iname "*.cpp" -execdir basename {} .cpp ';')))


all: suffix_tree_tests algo

$(MAIN_BIN_FILE) : $(ALL_SOURCE_FILES)
	@$(CC) $(ALL_SOURCE_FILES) -o $@

$(SUFFIX_TREE_TESTS_DIR)/%.exe : $(SUFFIX_TREE_TESTS_DIR)/%.cpp $(SUFFIX_TREE_SOURCE_FILES)
	$(CC) $< $(SUFFIX_TREE_SOURCE_FILES) -o $@

algo : $(MAIN_BIN_FILE)
	@./$<

suffix_tree_tests: $(SUFFIX_TREE_TESTS)
	$(addsuffix ;, $(addprefix ./, $(SUFFIX_TREE_TESTS)))

clean:
	@rm $(SUFFIX_TREE_TESTS_DIR)/*.exe $(MAIN_BIN_FILE)
