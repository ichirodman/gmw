CC = g++
ALL_CPP_FILES = algos/*.cpp utils/*.cpp alignment.cpp
OUTPUT_FILE = main

all:
	make alignment

alignment:
	$(CC) $(ALL_CPP_FILES) -o $(OUTPUT_FILE) && ./$(OUTPUT_FILE)

clean:
	rm $(OUTPUT_FILE)
