#include "SuffixTree.hpp"
#include <assert.h>
#include <string>
#include <iostream>


void handleNextSuffix(SuffixTreeBuilder *, SuffixTreeVertex *, std::string);

std::pair<SuffixTreeVertex *, std::string> goUpUntilFoundPrefixLink(SuffixTreeBuilder *, 
                                                SuffixTreeVertex *, char);

std::pair<SuffixTreeVertex *, std::string> goDownUntilSuffixSuperimposes(SuffixTreeBuilder *,
                                                SuffixTreeVertex *, std::string);

SuffixTreeVertex * getChildWithPrefixChar(SuffixTreeBuilder *, SuffixTreeVertex *, char);

bool hasChildWithPrefixChar(SuffixTreeBuilder *, SuffixTreeVertex *, char);

bool isVertexSubstringSuperimposesWithSuffix(SuffixTreeBuilder *, SuffixTreeVertex *, std::string);

void SuffixTreeBuilder::build() {
    SuffixTreeVertex * lastLeafVertex = const_cast<SuffixTreeVertex *>(this->getRoot());
    for (int i = 1, stringLength = this->suffixTreeString.length(); i <= stringLength; ++i) {
        std::string nextSuffix = this->getSuffixTreeSubstring(stringLength - i, i);
        handleNextSuffix(this, lastLeafVertex, nextSuffix);
    }
}

void handleNextSuffix(SuffixTreeBuilder * builder, SuffixTreeVertex * previousLeafVertex, 
                      std::string nextSuffix) {
    using std::pair;

    pair<SuffixTreeVertex *, std::string> vertexWithPrefixLinkAndRestoredSuffix = 
        goUpUntilFoundPrefixLink(builder, previousLeafVertex, nextSuffix.at(0));
    SuffixTreeVertex * previousBranchVertexWithPrefixLink = vertexWithPrefixLinkAndRestoredSuffix.first;
    std::string suffixString = vertexWithPrefixLinkAndRestoredSuffix.second;
    
    SuffixTreeVertex * nextBranchPrefixLinkedVertex = 
        previousBranchVertexWithPrefixLink->isRoot() ? previousBranchVertexWithPrefixLink : 
            previousBranchVertexWithPrefixLink->getPrefixLinkedVertex(nextSuffix.at(0));
    pair<SuffixTreeVertex *, std::string> buildInPlaceVertexAndLeftoverSuffix =
        goDownUntilSuffixSuperimposes(builder, nextBranchPrefixLinkedVertex, suffixString);
    SuffixTreeVertex * buildInPlaceVertex = buildInPlaceVertexAndLeftoverSuffix.first;
    suffixString = buildInPlaceVertexAndLeftoverSuffix.second;


}

std::pair<SuffixTreeVertex *, std::string> goUpUntilFoundPrefixLink(SuffixTreeBuilder * builder, 
                                        SuffixTreeVertex * vertex, char prefixLinkedChar) {
    std::string restoredSuffixWhileGoUp = "";
    for (; !(vertex->isRoot()) && !(vertex->hasPrefixLinkedVertex(prefixLinkedChar)); vertex = vertex->getParent()) {
        restoredSuffixWhileGoUp += builder->getVertexSubstring(vertex);
    }
    return { vertex, restoredSuffixWhileGoUp };
}


std::pair<SuffixTreeVertex *, std::string> goDownUntilSuffixSuperimposes(SuffixTreeBuilder * builder,
                                                SuffixTreeVertex * currentVertex, std::string suffixString) {
    while (hasChildWithPrefixChar(builder, currentVertex, suffixString.at(0))) {
        SuffixTreeVertex * childTryToFollow = getChildWithPrefixChar(builder, currentVertex, suffixString.at(0));
        if (isVertexSubstringSuperimposesWithSuffix(builder, childTryToFollow, suffixString)) {
            std::string childSubstring = builder->getVertexSubstring(childTryToFollow);
            suffixString = suffixString.substr(childSubstring.length(), suffixString.length() - childSubstring.length());
            currentVertex = childTryToFollow;
        } else {
            break;
        }
    }
    return { currentVertex, suffixString };
}

SuffixTreeVertex * getChildWithPrefixChar(SuffixTreeBuilder * builder, SuffixTreeVertex * parent, char prefixChar) {
    for (int i = 0; i < parent->getChildren()->size(); ++i) {
        SuffixTreeVertex * child = parent->getChildren()->at(i);
        std::string childSubstring = builder->getVertexSubstring(child);
        if (childSubstring.at(0) == prefixChar) {
            return child;
        }
    }
    return nullptr;
}

bool hasChildWithPrefixChar(SuffixTreeBuilder * builder, SuffixTreeVertex * parent, char prefixChar) {
    return getChildWithPrefixChar(builder, parent, prefixChar) != nullptr;
}

bool isVertexSubstringSuperimposesWithSuffix(SuffixTreeBuilder * builder, SuffixTreeVertex * vertex, std::string suffixString) {
    std::string vertexSubstring = builder->getVertexSubstring(vertex);
    return suffixString.length() >= vertexSubstring.length() && 
        suffixString.substr(0, vertexSubstring.length()) == vertexSubstring;
}
