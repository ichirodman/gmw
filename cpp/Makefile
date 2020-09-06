CC = g++
ALIGNMENT_CPP_FILES = algos/*.cpp utils/*.cpp alignment.cpp
ALIGNMENT_OUTPUT_FILE = alignment

all:
	@$(CC) suffix_tree/*.cpp -o suffix_tree_test; make suffix_tree_test --no-print-directory

alignment:
	$(CC) $(ALIGNMENT_CPP_FILES) -o $(ALIGNMENT_OUTPUT_FILE) && ./$(ALIGNMENT_OUTPUT_FILE)

suffix_tree_test:
	@./suffix_tree_test

clean:
	rm $(ALIGNMENT_OUTPUT_FILE)

.PHONY: all alignment suffix_tree_test
