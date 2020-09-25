#ifndef SUFFIX_TREE_BUILDER
#define SUFFIX_TREE_BUILDER


#include <string>
#include "SuffixTreeVertex/SuffixTreeVertex.hpp"


class SuffixTreeBuilder {
public:
	SuffixTreeBuilder(std::string);
	~SuffixTreeBuilder();

	const SuffixTreeVertex * getRoot();
	
	std::string getSuffixTreeSubstring(int, int);

	std::string getVertexSubstring(SuffixTreeVertex *);

	int getTreeStringLength();

	void build();

private:
	const std::string suffixTreeString;
	const SuffixTreeVertex * root;
};


#endif
