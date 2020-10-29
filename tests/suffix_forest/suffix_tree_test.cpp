#include <assert.h>
#include <algorithm>
#include <iostream>

#include "../tests_maintenance.hpp"
#include "../../source/suffix_forest/suffix_tree/suffix_tree.hpp"


void getEntryIndexesTest();

int main() {
    printTestStarted("suffix tree");
	getEntryIndexesTest();
	printLastTestFinished();
	return 0;
}

template<typename T>
bool contains(std::vector<T> *, T);

void getEntryIndexesTest() {
	std::string suffixTreeString = "abacaba";
	SuffixTree * tree = new SuffixTree(suffixTreeString);

	auto entries = tree->getEntryIndexes("a");
	
	assert(entries->size() == 4);
	assert(contains(entries, 0));
	assert(contains(entries, 2));
	assert(contains(entries, 4));
	assert(contains(entries, 6));

	delete tree;
}

template<typename T>
bool contains(std::vector<T> * v, T val) {
	return std::find(v->begin(), v->end(), val) != v->end();
}
