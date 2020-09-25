#include "../../Source/SuffixTree/SuffixTree.hpp"
#include <assert.h>


void updateInfoTest();

void childAddTest();

void removeChildTest();

void addPrefixLinkedVertex();

void getPrefixLinkedVertex();

void parentSetTest();

void parentSetTest();

void rootClassificationTest();

void leafClassificationTest();

int main() {
	updateInfoTest();
	childAddTest();
	removeChildTest();
	addPrefixLinkedVertex();
	getPrefixLinkedVertex();	
	parentSetTest();
	parentSetTest();
	rootClassificationTest();
	leafClassificationTest();
	return 0;
}

void updateInfoTest() {
	int entryIndex = 1, substringLength = 3;
	SuffixTreeVertex * vertex = new SuffixTreeVertex(entryIndex, substringLength);
	
	assert(vertex->getInfo().first == entryIndex && vertex->getInfo().second == substringLength);
}

void childAddTest() {
	SuffixTreeVertex * parent = new SuffixTreeVertex(0, 0),
		* child = new SuffixTreeVertex(0, 0);
	
	parent->addChildRelation(child);
	
	assert(parent->getChildren()->size() == 1);
	assert(parent->getChildren()->at(0) == child);
}

template <typename T>
bool isElementExist(std::vector<T *> * v, T * elem);

void removeChildTest() {
	SuffixTreeVertex * parent = new SuffixTreeVertex(0, 0),
		* child1 = new SuffixTreeVertex(0, 0), 
		* child2 = new SuffixTreeVertex(0, 0),
		* child3 = new SuffixTreeVertex(0, 0);
	
	parent->addChildRelation(child1);
	parent->addChildRelation(child2);
	parent->addChildRelation(child3);
	parent->removeChildRelation(child2);

	auto * children = parent->getChildren();
	assert(parent->getChildren()->size() == 2);
	assert(isElementExist(children, child1));
	assert(isElementExist(children, child3));
	assert(!isElementExist(children, child2));
}

void addPrefixLinkedVertex() {
	SuffixTreeVertex * independentVertex = new SuffixTreeVertex(0, 0),
		* prefixLinkedVertex = new SuffixTreeVertex(0, 0);
	char prefixLink = 'c';

	independentVertex->addPrefixLinkedVertex(prefixLinkedVertex, prefixLink);

	assert(independentVertex->hasPrefixLinkedVertex(prefixLink));
}

void getPrefixLinkedVertex() {
	SuffixTreeVertex * independentVertex = new SuffixTreeVertex(0, 0),
		* prefixLinkedVertex = new SuffixTreeVertex(0, 0);
	char prefixLink = 'c';

	independentVertex->addPrefixLinkedVertex(prefixLinkedVertex, prefixLink);

	assert(independentVertex->getPrefixLinkedVertex(prefixLink) == prefixLinkedVertex);
}

void parentSetTest() {
	SuffixTreeVertex * parent = new SuffixTreeVertex(0, 0),
		* child = new SuffixTreeVertex(0, 0);
	
	parent->addChildRelation(child);
	
	assert(child->getParent() == parent);
}

void rootClassificationTest() {
	SuffixTreeVertex * rootVertex = new SuffixTreeVertex(0, 0),
		* leafVertex = new SuffixTreeVertex(0, 0);

	rootVertex->addChildRelation(leafVertex);

	assert(rootVertex->isRoot());
	assert(!leafVertex->isRoot());
}

void leafClassificationTest() {
	SuffixTreeVertex * rootVertex = new SuffixTreeVertex(0, 0),
		* leafVertex = new SuffixTreeVertex(0, 0);

	rootVertex->addChildRelation(leafVertex);

	assert(leafVertex->isLeaf());
	assert(!leafVertex->isRoot());
}

template <typename T>
bool isElementExist(std::vector<T *> * v, T * elem) {
	for (int i = 0; i < v->size(); ++i) {
		if (v->at(i) == elem) {
			return true;
		}
	}
	return false;
}
