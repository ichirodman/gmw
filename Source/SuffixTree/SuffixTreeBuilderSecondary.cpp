#include "SuffixTree.h"

#define SPECIAL_END_CHAR "$"


SuffixTreeBuilder::SuffixTreeBuilder(std::string suffixTreeString) 
    : suffixTreeString(suffixTreeString + SPECIAL_END_CHAR), root(new SuffixTreeVertex(0, 0)) {}

SuffixTreeBuilder::~SuffixTreeBuilder() {
    delete this->root;
}

const SuffixTreeVertex * SuffixTreeBuilder::getRoot() {
    return this->root;
}

std::string SuffixTreeBuilder::getVertexSubstring(SuffixTreeVertex * vertex) {
    std::pair<int, int> entryIndexAndSubstringLength = vertex->getInfo();
    return this->suffixTreeString.substr(entryIndexAndSubstringLength.first, 
                                         entryIndexAndSubstringLength.second);
}
