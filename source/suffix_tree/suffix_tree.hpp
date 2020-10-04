#ifndef SUFFIX_TREE
#define SUFFIX_TREE


#include <string>
#include "builder/suffix_tree_builder.hpp"
#include "builder/vertex/suffix_tree_vertex.hpp"


class SuffixTree {
public:
	SuffixTree(const std::string &);
	
	~SuffixTree();

	int getEntryIndex(std::string);

private:
	SuffixTreeBuilder * builder;
};


#endif
