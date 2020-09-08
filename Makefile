CC = g++

TEST_DIRNAME=tests

SUFFIX_TREE_TEST_FILES=suffix_tree_test.cpp
SUFFIX_TREE_TEST_BIN=suffix_tree_test

all:
	echo "There's nothing to compile :)"

tests: suffix_tree_test

suffix_tree_test:
	$(CC) $(TEST_DIRNAME)/$(SUFFIX_TREE_TEST_FILES) -o $(SUFFIX_TREE_TEST_BIN); ./$(SUFFIX_TREE_TEST_BIN)

$(SUFFIX_TREE_TEST_BIN): $(TEST_DIRNAME)/$(SUFFIX_TREE_TEST_FILES)

clean:
	rm $(SUFFIX_TREE_TEST_BIN)

.PHONY: all suffix_tree_test
