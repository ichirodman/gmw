//
// Created by ichigo on 18.10.2020.
//

#ifndef GMW_SUFFIX_FOREST_HPP
#define GMW_SUFFIX_FOREST_HPP

#define SUFFIX_TREE_STRING_MAX_LENGTH 10000

#include <vector>
#include "../utils/fasta.hpp"
#include "suffix_tree/suffix_tree.hpp"

class SuffixForest {
public:
    SuffixForest(FastaSequence *);

    void build();

    std::vector<int> *getEntryIndexes(std::string);

private:
    FastaSequence *sequence;

    std::vector<SuffixTree *> *suffixTrees;
};

#endif //GMW_SUFFIX_FOREST_HPP
