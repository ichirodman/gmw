#include "suffix_tree.hpp"
#include "builder/subsidary/subsidary.hpp"
#include <iostream>
#include <string>

SuffixTree::SuffixTree(const std::string & inp) {
	this->builder = new SuffixTreeBuilder(inp);
	this->builder->build();
}

SuffixTree::~SuffixTree() {
	delete this->builder;
}

void getRecursiveDownAndCountLeafs(SuffixTreeVertex *, std::vector<int> *, int);

std::vector<int> * SuffixTree::getEntryIndexes(std::string substring) { 
	auto farestVertexAndRemainingSuffix = goDownUntilSuffixSuperimposes(this->builder, this->builder->getRoot(), substring);
	std::vector<int> * entries = new std::vector<int>();
	getRecursiveDownAndCountLeafs(farestVertexAndRemainingSuffix.first, entries, 
		farestVertexAndRemainingSuffix.second.length());
	return entries;
}

void getRecursiveDownAndCountLeafs(SuffixTreeVertex * vertex, std::vector<int> * entries, int prefixLen) {
	if(vertex->getChildren()->size() > 0) {
		for (int i = 0; i < vertex->getChildren()->size(); ++i) {
			SuffixTreeVertex * child = vertex->getChildren()->at(i);
			getRecursiveDownAndCountLeafs(child, entries, prefixLen + child->getInfo().second);
		}
	} else {
		entries->push_back(prefixLen - 1);
	}
}
