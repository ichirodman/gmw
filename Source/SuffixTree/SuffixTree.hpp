#ifndef SUFFIX_TREE
#define SUFFIX_TREE


#include <string>
#include "SuffixTreeBuilder/SuffixTreeBuilder.hpp"
#include "SuffixTreeBuilder/SuffixTreeVertex/SuffixTreeVertex.hpp"


class SuffixTree {
public:
	SuffixTree(const std::string &);
	
	~SuffixTree();

	int getEntryIndex(std::string);

private:
	SuffixTreeBuilder * builder;
};


#endif
