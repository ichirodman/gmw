CC = g++ -std=gnu++0x

MAIN_ALGO_FILE = main.cpp
MAIN_BIN_FILE = main_bin.exe

SOURCE_DIRNAME = Source
TEST_DIRNAME = Tests
SUFFIX_TREE_TESTS_DIR := $(TEST_DIRNAME)/SuffixTree

UTILS_FILES = $(shell find ./$(SOURCE_DIRNAME)/Utils -name "*.cpp")
SUFFIX_TREE_SOURCE_FILES = $(shell find ./$(SOURCE_DIRNAME)/SuffixTree -name "*.cpp")

ALL_SOURCE_FILES := $(shell find ./$(SOURCE_DIRNAME) -name "*.cpp")

SUFFIX_TREE_TESTS := $(addprefix $(SUFFIX_TREE_TESTS_DIR)/, SuffixTreeTest.exe SuffixTreeVertexTest.exe SuffixTreeBuilderTest.exe)


all: suffix_tree_tests algo

$(MAIN_BIN_FILE) : $(ALL_SOURCE_FILES)
	@$(CC) $(ALL_SOURCE_FILES) -o $@

$(SUFFIX_TREE_TESTS_DIR)/%.exe : $(SUFFIX_TREE_TESTS_DIR)/%.cpp $(SUFFIX_TREE_SOURCE_FILES)
	@$(CC) $< $(SUFFIX_TREE_SOURCE_FILES) -o $@

algo : $(MAIN_BIN_FILE)
	@./$<

suffix_tree_tests: $(SUFFIX_TREE_TESTS)
	@$(addsuffix ;, $(addprefix ./, $(SUFFIX_TREE_TESTS)))

clean:
	@rm $(SUFFIX_TREE_TESTS_DIR)/*.exe $(MAIN_BIN_FILE)
