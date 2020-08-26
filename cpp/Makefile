CC = g++
ALIGNMENT_CPP_FILES = algos/*.cpp utils/*.cpp alignment.cpp
ALIGNMENT_OUTPUT_FILE = alignment

all:
	make alignment

alignment:
	$(CC) $(ALIGNMENT_CPP_FILES) -o $(ALIGNMENT_OUTPUT_FILE) && ./$(ALIGNMENT_OUTPUT_FILE)



clean:
	rm $(ALIGNMENT_OUTPUT_FILE)
