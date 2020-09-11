#include "SuffixTree.h"
#include <iostream>

SuffixTreeVertex::SuffixTreeVertex(int entryIndex, int substringLength) 
	: parent(nullptr), suffixTreeStringEntryIndex(entryIndex), suffixTreeStringSubstringLength(substringLength) {
	this->children = new std::vector<SuffixTreeVertex *>();
}

SuffixTreeVertex::~SuffixTreeVertex() {
	delete this->children;
}

void SuffixTreeVertex::updateInfo(int entryIndex, int substringLength) {
	this->suffixTreeStringEntryIndex = entryIndex; 
	this->suffixTreeStringSubstringLength = substringLength;
}

std::pair<int, int> SuffixTreeVertex::getInfo() {
	return std::pair<int, int>(this->suffixTreeStringEntryIndex, this->suffixTreeStringSubstringLength);
}

std::vector<SuffixTreeVertex *> * SuffixTreeVertex::getChildren() {
	return this->children;
}

void SuffixTreeVertex::addChildRelation(SuffixTreeVertex * childToAdd) {
	for (int i = 0; i < this->children->size(); ++i) {
		if (this->children->at(i) == childToAdd) {
			return;
		}
	}
	this->children->push_back(childToAdd);
	childToAdd->parent = this;
}

void SuffixTreeVertex::removeChildRelation(SuffixTreeVertex * childToRemove) {
	for (int i = 0; i < this->children->size(); ++i) {
		SuffixTreeVertex * child = this->children->at(i);
		if (child == childToRemove) {
			this->children->erase(this->children->begin() + i);
			child->parent = nullptr;
		}
	}
}
	
SuffixTreeVertex * SuffixTreeVertex::getParent() {
	return this->parent;
}


bool SuffixTreeVertex::isRoot() {
	return this->parent == nullptr;
}

bool SuffixTreeVertex::isLeaf() {
	return this->children->size() == 0;
}
