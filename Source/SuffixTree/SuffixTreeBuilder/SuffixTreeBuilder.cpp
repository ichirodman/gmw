#include "SuffixTreeBuilder.hpp"
#include "SuffixTreeVertex/SuffixTreeVertex.hpp"
#include "BuildSubsidary/BuildSubsidary.hpp"
#include <string>
#include <iostream>


#define SPECIAL_END_CHAR "$"


void SuffixTreeBuilder::build() {
    SuffixTreeVertex * lastLeafBuiltVertex = const_cast<SuffixTreeVertex *>(this->getRoot());
    for (int i = 1, stringLength = this->suffixTreeString.length(); i <= stringLength; ++i) {
        std::string nextSuffix = this->getSuffixTreeSubstring(stringLength - i, i);
        std::cout << "Next suffix: " << nextSuffix << std::endl;
        lastLeafBuiltVertex = handleNextSuffixAndGetNewLeaf(this, lastLeafBuiltVertex, nextSuffix);
    }
}

SuffixTreeBuilder::SuffixTreeBuilder(std::string suffixTreeString) 
    : suffixTreeString(suffixTreeString + SPECIAL_END_CHAR), root(new SuffixTreeVertex(0, 0)) {}

SuffixTreeBuilder::~SuffixTreeBuilder() {
    delete this->root;
}

SuffixTreeVertex * SuffixTreeBuilder::getRoot() {
    return this->root;
}

std::string SuffixTreeBuilder::getSuffixTreeSubstring(int entryIndex, int substringLength) {
    return this->suffixTreeString.substr(entryIndex, substringLength);
}

std::string SuffixTreeBuilder::getVertexSubstring(SuffixTreeVertex * vertex) {
    std::pair<int, int> entryIndexAndSubstringLength = vertex->getInfo();
    return this->getSuffixTreeSubstring(entryIndexAndSubstringLength.first, entryIndexAndSubstringLength.second);
}

int SuffixTreeBuilder::getTreeStringLength() {
    return this->suffixTreeString.length();
}
