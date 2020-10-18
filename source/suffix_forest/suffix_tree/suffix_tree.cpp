#include "suffix_tree.hpp"
#include "builder/subsidary/subsidary.hpp"
#include <string>

SuffixTree::SuffixTree(std::string &sequence) {
    this->builder = new SuffixTreeBuilder(sequence);
    this->builder->build();
}

SuffixTree::~SuffixTree() {
    delete this->builder;
}

void getRecursiveDownAndCountLeaves(SuffixTreeVertex *vertex, std::vector<int> *entries, int prefixLen);

std::vector<int> *SuffixTree::getEntryIndexes(std::string substring) {
    auto farthestVertexAndRemainingSuffix = goDownUntilSuffixSuperimposes(this->builder, this->builder->getRoot(),
                                                                        substring);
    std::vector<int> *entries = new std::vector<int>();
    getRecursiveDownAndCountLeaves(farthestVertexAndRemainingSuffix.first, entries,
                                  farthestVertexAndRemainingSuffix.second.length());
    return entries;
}

void getRecursiveDownAndCountLeaves(SuffixTreeVertex *vertex, std::vector<int> *entries, int prefixLen) {
    if (vertex->getChildren()->size() > 0) {
        for (int i = 0; i < vertex->getChildren()->size(); ++i) {
            SuffixTreeVertex *child = vertex->getChildren()->at(i);
            getRecursiveDownAndCountLeaves(child, entries, prefixLen + child->getInfo().second);
        }
    } else {
        entries->push_back(prefixLen - 1);
    }
}
