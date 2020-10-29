//
// Created by ichigo on 18.10.2020.
//

#include "suffix_forest.hpp"
#include <iostream>
#include <functional>

SuffixForest::SuffixForest(FastaSequence *fastaSequence)
        : sequence(fastaSequence), suffixTrees(new std::vector<SuffixTree *>()) {}

void SuffixForest::build() {
    // TODO remove debug prints
    int sequenceLength = this->sequence->source->length(),
            additiveLength = sequenceLength - SUFFIX_TREE_STRING_MIN_LENGTH *
                                              (sequenceLength / SUFFIX_TREE_STRING_MIN_LENGTH),
            sliceLength = SUFFIX_TREE_STRING_MIN_LENGTH + additiveLength,
            suffixTreesAmount = sequenceLength / sliceLength;
    std::cout << "TOTAL SEQUENCE LENGTH : " << sequenceLength << std::endl;
    std::cout << "Going to build " << suffixTreesAmount << " suffix trees" << std::endl;
    for (int sliceEntry = 0, i = 1; sequenceLength - sliceEntry > sliceLength; sliceEntry += sliceLength, i++) {
        int currentSliceLength = sequenceLength - sliceEntry < sliceLength * 2 ?
                                 sequenceLength - sliceEntry : sliceLength;
        std::string sequenceSlice = this->sequence->source->substr(sliceEntry, currentSliceLength);
        auto *suffixTree = new SuffixTree(sequenceSlice);
        this->suffixTrees->push_back(suffixTree);
        std::cout << "Entry : " << sliceEntry << " len: " << currentSliceLength << std::endl;
        std::cout << "Built suffix tree num. " << i << ", left to build: " << (suffixTreesAmount - i) << std::endl;
    }
}

void supplement(std::vector<int> *, std::vector<int> *);

std::vector<int> *SuffixForest::getEntryIndexes(const std::string &substring) {
    auto *globalEntries = new std::vector<int>();
    for (auto suffixTree : *this->suffixTrees) {
        std::vector<int> *treeEntries = suffixTree->getEntryIndexes(substring);
        supplement(globalEntries, treeEntries);
    }
    return globalEntries;
}

bool contains(std::vector<int> *, int);

void supplement(std::vector<int> *main, std::vector<int> *additional) {
    for (int element : *additional) {
        if (!contains(main, element)) {
            main->push_back(element);
        }
    }
}

bool contains(std::vector<int> *v, int val) {
    std::function<bool(int)> equalToVal = [&val](int element) { return element == val; };
    return std::any_of(v->begin(), v->end(), equalToVal);
}
