CC = g++

SUFFIX_TREE_TEST_FILES=Tests/SuffixTree/SuffixTreeTest.cpp Source/SuffixTree/*.cpp
SUFFIX_TREE_VERTEX_TEST_FILES=Tests/SuffixTree/SuffixTreeVertexTest.cpp Source/SuffixTree/*.cpp
OUTPUT_BIN=LastCompilationBin

all:
	@echo "There's nothing to compile :)"

tests: suffix_tree_test suffix_tree_vertex_test

suffix_tree_test:
	$(CC) $(SUFFIX_TREE_TEST_FILES) -o $(OUTPUT_BIN); ./$(OUTPUT_BIN)

suffix_tree_vertex_test:
	$(CC) $(SUFFIX_TREE_VERTEX_TEST_FILES) -o $(OUTPUT_BIN); ./$(OUTPUT_BIN)

$(OUTPUT_BIN): $(SUFFIX_TREE_TEST_FILES)

clean:
	@rm $(OUTPUT_BIN)

.PHONY: all suffix_tree_test
