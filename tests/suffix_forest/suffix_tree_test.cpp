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
    std::string suffixTreeString = "abacababdf";
    SuffixTree *tree = new SuffixTree(suffixTreeString, 0);

    auto entries = tree->getEntryIndexes("a");

    for (int i = 0; i < entries->size(); ++i)
        std::cout << entries->at(i) << " ";
    std::cout << std::endl;

    assert(entries->size() == 4);
    assert(contains(entries, 0));
    assert(contains(entries, 2));
    assert(contains(entries, 4));
    assert(contains(entries, 6));

    delete tree;
}

template<typename T>
bool contains(std::vector<T> *v, T val) {
    return std::find(v->begin(), v->end(), val) != v->end();
}
