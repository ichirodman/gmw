CC = g++ -std=gnu++0x

MAIN_ALGO_FILE = main.cpp
MAIN_OUTPUT_FILE = main_bin.exe

SOURCE_DIRNAME = Source
TEST_DIRNAME = Tests
SUFFIX_TREE_TESTS_DIR := $(TEST_DIRNAME)/SuffixTree

UTILS_FILES = $(shell find ./$(SOURCE_DIRNAME)/Utils -name "*.cpp")
SUFFIX_TREE_SOURCE_FILES = $(shell find ./$(SOURCE_DIRNAME)/SuffixTree -name "*.cpp")

SUFFIX_TREE_TESTS := $(addprefix $(SUFFIX_TREE_TESTS_DIR)/, SuffixTreeTest.exe SuffixTreeVertexTest.exe SuffixTreeBuilderTest.exe)


all:
	$(CC) ./$(SOURCE_DIRNAME)/$(MAIN_ALGO_FILE) \
	$(UTILS_FILES) $(SUFFIX_TREE_SOURCE_FILES) \
	-o $(SOURCE_DIRNAME)/$(MAIN_OUTPUT_FILE) && ./$(SOURCE_DIRNAME)/$(MAIN_OUTPUT_FILE)

$(SUFFIX_TREE_TESTS_DIR)/%.exe : $(SUFFIX_TREE_TESTS_DIR)/%.cpp
	$(CC) $< $(SUFFIX_TREE_SOURCE_FILES) -o $@ && ./$@

suffix_tree_tests: $(SUFFIX_TREE_TESTS)

clean:
	@rm $(shell find . -name "*.exe")

.PHONY: all suffix_tree_tests
