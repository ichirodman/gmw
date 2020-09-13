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

std::string SuffixTreeBuilder::getSuffixTreeSubstring(int entryIndex, int substringLength) {
    return this->suffixTreeString.substr(entryIndex, substringLength);
}

std::string SuffixTreeBuilder::getVertexSubstring(SuffixTreeVertex * vertex) {
    std::pair<int, int> entryIndexAndSubstringLength = vertex->getInfo();
    return this->getSuffixTreeSubstring(entryIndexAndSubstringLength.first, entryIndexAndSubstringLength.second);
}
