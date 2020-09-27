CC = g++

MAIN_ALGO_FILE=Source/main.cpp

UTILS_FILES=$(shell find ./Source/Utils -name "*.cpp")

SUFFIX_TREE_SOURCE_FILES=$(shell find ./Source/SuffixTree -name "*.cpp")

SUFFIX_TREE_TEST_FILES=Tests/SuffixTree/SuffixTreeTest.cpp
SUFFIX_TREE_VERTEX_TEST_FILES=Tests/SuffixTree/SuffixTreeVertexTest.cpp
SUFFIX_TREE_BUILDER_TEST_FILES=Tests/SuffixTree/SuffixTreeBuilderTest.cpp

OUTPUT_BIN=LastCompilationBin


all:
	$(CC) $(MAIN_ALGO_FILE) $(UTILS_FILES) $(SUFFIX_TREE_SOURCE_FILES) -o $(OUTPUT_BIN); ./$(OUTPUT_BIN)

tests: suffix_tree_test suffix_tree_builder_test suffix_tree_vertex_test

suffix_tree_test:
	$(CC) $(SUFFIX_TREE_TEST_FILES) $(SUFFIX_TREE_SOURCE_FILES) -o $(OUTPUT_BIN); ./$(OUTPUT_BIN)

suffix_tree_builder_test:
	$(CC) $(SUFFIX_TREE_BUILDER_TEST_FILES) $(SUFFIX_TREE_SOURCE_FILES) -o $(OUTPUT_BIN); ./$(OUTPUT_BIN)

suffix_tree_vertex_test:
	$(CC) $(SUFFIX_TREE_VERTEX_TEST_FILES) $(SUFFIX_TREE_SOURCE_FILES) -o $(OUTPUT_BIN); ./$(OUTPUT_BIN)

$(OUTPUT_BIN): $(SUFFIX_TREE_TEST_FILES)

clean:
	@rm $(OUTPUT_BIN)

.PHONY: all tests
