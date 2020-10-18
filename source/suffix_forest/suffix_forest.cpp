//
// Created by ichigo on 18.10.2020.
//

#include "suffix_forest.hpp"
#include <iostream>

SuffixForest::SuffixForest(FastaSequence *fastaSequence)
        : sequence(fastaSequence), suffixTrees(new std::vector<SuffixTree *>()) {}

void SuffixForest::build() {
    int suffixTreesAmount = (this->sequence->source->length() + SUFFIX_TREE_STRING_MAX_LENGTH - 1)
                            / SUFFIX_TREE_STRING_MAX_LENGTH;
    std::cout << "Going to build " << suffixTreesAmount << " suffix trees" << std::endl;
    for (int sliceEntry = 0, i = 1, sequenceLength = this->sequence->source->length();
         sliceEntry < sequenceLength; sliceEntry += SUFFIX_TREE_STRING_MAX_LENGTH, i++) {
        int sliceLength = sequenceLength - sliceEntry < SUFFIX_TREE_STRING_MAX_LENGTH ?
                          sequenceLength - sliceEntry : SUFFIX_TREE_STRING_MAX_LENGTH;
        std::string sequenceSlice = this->sequence->source->substr(sliceEntry, sliceLength);
        SuffixTree *suffixTree = new SuffixTree(sequenceSlice);
        this->suffixTrees->push_back(suffixTree);
        std::cout << "Built suffix tree num. " << i << ", left to build: " << (suffixTreesAmount - i) << std::endl;
    }
}

void supplement(std::vector<int> *, std::vector<int> *);

std::vector<int> *SuffixForest::getEntryIndexes(std::string substring) {
    std::vector<int> *globalEntries = new std::vector<int>();
    for (int i = 0; i < this->suffixTrees->size(); ++i) {
        SuffixTree *suffixTree = this->suffixTrees->at(i);
        std::vector<int> *treeEntries = suffixTree->getEntryIndexes(substring);
        supplement(globalEntries, treeEntries);
    }
    return globalEntries;
}

bool contains(std::vector<int> *, int);

void supplement(std::vector<int> *main, std::vector<int> *additional) {
    for (int i = 0; i < additional->size(); ++i) {
        int element = additional->at(i);
        if (!contains(main, element)) {
            main->push_back(element);
        }
    }
}

bool contains(std::vector<int> *v, int val) {
    for (int i = 0; i < v->size(); ++i) {
        if (v->at(i) == val) {
            return true;
        }
    }
    return false;
}