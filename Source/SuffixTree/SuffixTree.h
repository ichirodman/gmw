#ifndef SUFFIX_TREE
#define SUFFIX_TREE


#include <string>
#include <vector>


class SuffixTreeBuilder;

class SuffixTreeVertex;

class SuffixTree {
public:
	SuffixTree(const std::string &);
	
	~SuffixTree();

	int getEntryIndex(std::string);

private:
	SuffixTreeBuilder * builder;
};

class SuffixTreeBuilder {
public:
	SuffixTreeBuilder(std::string);
	~SuffixTreeBuilder();

	const SuffixTreeVertex * getRoot();
	
	std::string getVertexSubstring(SuffixTreeVertex *);

	void build();

private:
	const std::string suffixTreeString;
	const SuffixTreeVertex * root;
};


class SuffixTreeVertex {
public:
	SuffixTreeVertex(int, int);

	~SuffixTreeVertex();

	void updateInfo(int, int);

	std::pair<int, int> getInfo();

	std::vector<SuffixTreeVertex *> * getChildren();

	void addChildRelation(SuffixTreeVertex *);

	void removeChildRelation(SuffixTreeVertex *);
	
	void addPrefixLinkedVertex(SuffixTreeVertex *, char);

	SuffixTreeVertex * getPrefixLinkedVertex(char);

	bool hasPrefixLinkedVertex(char);

	SuffixTreeVertex * getParent();

	bool isRoot();

	bool isLeaf();

private:
	std::vector<SuffixTreeVertex *> * children;
	std::vector<SuffixTreeVertex *> * prefixLinkedVertexes;
	std::vector<char> * prefixLinkedChars;
	SuffixTreeVertex * parent;
	int suffixTreeStringEntryIndex, suffixTreeStringSubstringLength;
};


#endif
