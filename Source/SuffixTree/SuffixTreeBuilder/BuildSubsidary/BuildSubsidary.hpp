#ifndef BUILD_SUBSIDARY_FUNCTIONS
#define BUILD_SUBSIDARY_FUNCTIONS


#include "../../SuffixTree.hpp"
#include "../SuffixTreeBuilder.hpp"
#include "../SuffixTreeVertex/SuffixTreeVertex.hpp"


SuffixTreeVertex * handleNextSuffixAndGetNewLeaf(SuffixTreeBuilder *, SuffixTreeVertex *, std::string &);

std::pair<SuffixTreeVertex *, std::string> goUpUntilFoundPrefixLink(SuffixTreeBuilder *,  SuffixTreeVertex *, char);

std::pair<SuffixTreeVertex *, std::string> goDownUntilSuffixSuperimposes(SuffixTreeBuilder *, SuffixTreeVertex *, std::string &);

SuffixTreeVertex * getChildWithPrefixChar(SuffixTreeBuilder *, SuffixTreeVertex *, char);

bool hasChildWithPrefixChar(SuffixTreeBuilder *, SuffixTreeVertex *, char);

bool isVertexSubstringSuperimposesWithSuffix(SuffixTreeBuilder *, SuffixTreeVertex *, std::string &);

SuffixTreeVertex * forkBranchAndGetNewLeaf(SuffixTreeBuilder *, SuffixTreeVertex *, std::string &);

SuffixTreeVertex * splitBranchWhileSuffixSuperimposesAndGetSplitPlaceVertex(SuffixTreeBuilder *, SuffixTreeVertex *, std::string &);

void buildInIntermediary(SuffixTreeVertex * parent, SuffixTreeVertex * child, SuffixTreeVertex * intermediary);

int getOverlayLength(std::string &, std::string &);

SuffixTreeVertex * addLeafToVertex(SuffixTreeBuilder *, SuffixTreeVertex *, std::string &);

SuffixTreeVertex * createIndependentLeafVertex(SuffixTreeBuilder *, std::string &);

void goUpTheBranchesAndAddPrefixLinksIfNecessary(SuffixTreeBuilder * builder, 
    SuffixTreeVertex * oldLeaf, SuffixTreeVertex * newLeaf, char prefixChar);

#endif
