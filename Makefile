CC = g++

SUFFIX_TREE_TEST_FILES=tests/suffix_tree/suffix_tree_test.cpp src/suffix_tree/*.cpp
SUFFIX_TREE_VERTEX_TEST_FILES=tests/suffix_tree/suffix_tree_vertex_test.cpp src/suffix_tree/*.cpp
OUTPUT_BIN=suffix_tree_test

all:
	echo "There's nothing to compile :)"

tests: suffix_tree_test, suffix_tree_vertex_test

suffix_tree_test:
	$(CC) $(SUFFIX_TREE_TEST_FILES) -o $(OUTPUT_BIN); ./$(OUTPUT_BIN)

suffix_tree_vertex_test:
	$(CC) $(SUFFIX_TREE_VERTEX_TEST_FILES) -o $(OUTPUT_BIN); ./$(OUTPUT_BIN)

$(OUTPUT_BIN): $(SUFFIX_TREE_TEST_FILES)

clean:
	rm $(OUTPUT_BIN)

.PHONY: all suffix_tree_test
