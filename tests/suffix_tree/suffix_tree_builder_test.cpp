#include "../../source/suffix_tree/builder/suffix_tree_builder.hpp"
#include "../../source/suffix_tree/builder/subsidary/subsidary.hpp"
#include <assert.h>


void getRootTest();

void getVertexSubstringTest();

void getOverlayLengthTest();

void buildInIntermediaryTest();

void createIndependentLeafVertexTest();

void hasChildWithPrefixCharTest();

void getChildWithPrefixCharTest();

void isVertexSubstringSuperimposesWithSuffixTest();

void goUpUntilFoundPrefixLinkTest();

void goDownUntilSuffixSuperimposesTest();

void addLeafToVertexTest();

void goUpTheBranchesAndAddPrefixLinksIfNecessaryTest();

void splitBranchWhileSuffixSuperimposesAndGetSplitPlaceVertexTest();

void forkBranchAndGetNewLeafTest();

void handleNextSuffixAndGetNewLeafTest();

void buildTest();

SuffixTreeBuilder * createHelloWorldSuffixTreeBuilder();

std::string getSuffixTreeBuilderString(SuffixTreeBuilder *);

int main() {
    getRootTest();
    getVertexSubstringTest();
    getOverlayLengthTest();
    buildInIntermediaryTest();
    createIndependentLeafVertexTest();
    hasChildWithPrefixCharTest();
    getChildWithPrefixCharTest();
    isVertexSubstringSuperimposesWithSuffixTest();
    goUpUntilFoundPrefixLinkTest();
    goDownUntilSuffixSuperimposesTest();
    addLeafToVertexTest();
    goUpTheBranchesAndAddPrefixLinksIfNecessaryTest();
    splitBranchWhileSuffixSuperimposesAndGetSplitPlaceVertexTest();
    forkBranchAndGetNewLeafTest();
    handleNextSuffixAndGetNewLeafTest();
    buildTest();
    return 0;
}

void getRootTest() {
    const std::string sts = "ABABABABA";
    SuffixTreeBuilder * stb = new SuffixTreeBuilder(sts);

    assert(stb->getRoot() != nullptr);

    delete stb;
}

void getVertexSubstringTest() {
    std::string sts = "abracadabra";
    SuffixTreeBuilder * stb = new SuffixTreeBuilder(sts);

    int ei1 = 4, ei2 = 2, ei3 = 7;
    int sl1 = 0, sl2 = 5, sl3 = 2;
    SuffixTreeVertex * stv1 = new SuffixTreeVertex(ei1, sl1),
                    * stv2 = new SuffixTreeVertex(ei2, sl2),
                    * stv3 = new SuffixTreeVertex(ei3, sl3);

    assert(stb->getSuffixTreeSubstring(ei1, sl1) == sts.substr(ei1, sl1));
    assert(stb->getSuffixTreeSubstring(ei2, sl2) == sts.substr(ei2, sl2));
    assert(stb->getSuffixTreeSubstring(ei3, sl3) == sts.substr(ei3, sl3));

    assert(stb->getVertexSubstring(stv1) == sts.substr(ei1, sl1));
    assert(stb->getVertexSubstring(stv2) == sts.substr(ei2, sl2));
    assert(stb->getVertexSubstring(stv3) == sts.substr(ei3, sl3));

    delete stb;
    delete stv1, stv2, stv3;
}


void getOverlayLengthTest() {
    std::string equalSection = "abcdef", firstSuffix = "qwerty", secondSuffix = "asdfgg";
    std::string firstString = equalSection + firstSuffix, secondString = equalSection + secondSuffix;

    int overlayLength = getOverlayLength(firstString, secondString);

    assert(overlayLength == equalSection.length());
}

void buildInIntermediaryTest() {
    SuffixTreeVertex * parent = new SuffixTreeVertex(0, 0), 
        * child = new SuffixTreeVertex(0, 0), * intermediary = new SuffixTreeVertex(0, 0);

    buildInIntermediary(parent, child, intermediary);

    assert(child->getParent() == intermediary);
    assert(intermediary->getParent() == parent);
    assert(parent->getChildren()->at(0) == intermediary);
    assert(intermediary->getChildren()->at(0) == child);
    assert(parent->getChildren()->size() == 1);
    assert(intermediary->getChildren()->size() == 1);
}

void createIndependentLeafVertexTest() {
    SuffixTreeBuilder * builder = new SuffixTreeBuilder("hello_world");
    std::string treeString = builder->getSuffixTreeSubstring(0, builder->getTreeStringLength());
    int suffixLength = 6;
    std::string someSuffix = treeString.substr(treeString.length() - suffixLength, suffixLength);

    SuffixTreeVertex * leaf = createIndependentLeafVertex(builder, someSuffix);

    assert(builder->getVertexSubstring(leaf) == someSuffix);
    assert(leaf->getChildren()->size() == 0);
    assert(leaf->getParent() == nullptr);
}

void hasChildWithPrefixCharTest() {
    SuffixTreeBuilder * builder = createHelloWorldSuffixTreeBuilder();
    std::string suffixTreeString = getSuffixTreeBuilderString(builder);
    int firstCharEntryIndex = 0, secondCharEntryIndex = 1;
    char firstChar = suffixTreeString.at(firstCharEntryIndex),
        secondChar = suffixTreeString.at(firstCharEntryIndex);
    SuffixTreeVertex * firstCharChild = new SuffixTreeVertex(firstCharEntryIndex, 1),
        * secondCharChild = new SuffixTreeVertex(secondCharEntryIndex, 1);
    SuffixTreeVertex * root = const_cast<SuffixTreeVertex *>(builder->getRoot());
    
    root->addChildRelation(firstCharChild);
    root->addChildRelation(secondCharChild);

    assert(hasChildWithPrefixChar(builder, root, firstChar));
    assert(hasChildWithPrefixChar(builder, root, secondChar));
}

void getChildWithPrefixCharTest() {
    SuffixTreeBuilder * builder = createHelloWorldSuffixTreeBuilder();
    std::string suffixTreeString = getSuffixTreeBuilderString(builder);
    int firstCharEntryIndex = 0, secondCharEntryIndex = 1;
    char firstChar = suffixTreeString.at(firstCharEntryIndex),
        secondChar = suffixTreeString.at(secondCharEntryIndex);
    SuffixTreeVertex * firstCharChild = new SuffixTreeVertex(firstCharEntryIndex, 1),
        * secondCharChild = new SuffixTreeVertex(secondCharEntryIndex, 1);
    SuffixTreeVertex * root = const_cast<SuffixTreeVertex *>(builder->getRoot());
    
    root->addChildRelation(firstCharChild);
    root->addChildRelation(secondCharChild);

    assert(getChildWithPrefixChar(builder, root, firstChar) == firstCharChild);
    assert(getChildWithPrefixChar(builder, root, secondChar) == secondCharChild);
}

void isVertexSubstringSuperimposesWithSuffixTest() {
    SuffixTreeBuilder * builder = createHelloWorldSuffixTreeBuilder();
    int vertexSubstringLength = 5;
    SuffixTreeVertex * vertex = new SuffixTreeVertex(0, vertexSubstringLength),
        * root = const_cast<SuffixTreeVertex *>(builder->getRoot());
    root->addChildRelation(vertex);

    std::string stringToSuperimpose = builder->getVertexSubstring(vertex).substr(0, vertexSubstringLength + 2);

    assert(isVertexSubstringSuperimposesWithSuffix(builder, vertex, stringToSuperimpose));
}

void goUpUntilFoundPrefixLinkTest() {
    SuffixTreeBuilder * builder = createHelloWorldSuffixTreeBuilder();
    int entryIndex = 2, substringLength = 5;
    SuffixTreeVertex * firstBranchFirstDeepVertex = new SuffixTreeVertex(0, 0),
        * firstBranchSecondDeepVertex = new SuffixTreeVertex(0, 0),
        * firstBranchThirdDeepVertex = new SuffixTreeVertex(entryIndex, substringLength),
        * secondBranchFirstDeepVertex = new SuffixTreeVertex(0, 0),
        * root = const_cast<SuffixTreeVertex *>(builder->getRoot());
    root->addChildRelation(firstBranchFirstDeepVertex);
    root->addChildRelation(secondBranchFirstDeepVertex);
    firstBranchFirstDeepVertex->addChildRelation(firstBranchSecondDeepVertex);
    firstBranchSecondDeepVertex->addChildRelation(firstBranchThirdDeepVertex);
    char prefixLinkChar = 'c';

    firstBranchSecondDeepVertex->addPrefixLinkedVertex(secondBranchFirstDeepVertex, prefixLinkChar);

    auto vertexWithPrefixLinkAndRestoredSuffix = goUpUntilFoundPrefixLink(builder, firstBranchThirdDeepVertex, prefixLinkChar);
    assert(vertexWithPrefixLinkAndRestoredSuffix.first == firstBranchSecondDeepVertex);
    assert(builder->getSuffixTreeSubstring(entryIndex, substringLength) == vertexWithPrefixLinkAndRestoredSuffix.second);
}

void goDownUntilSuffixSuperimposesTest() {
    SuffixTreeBuilder * builder = createHelloWorldSuffixTreeBuilder();
    int firstSubstringLength = 2, secondSubstringLength = 2, thirdSubstringLength = 3;
    SuffixTreeVertex * firstDeepVertex = new SuffixTreeVertex(0, firstSubstringLength),
        * secondDeepVertex = new SuffixTreeVertex(firstSubstringLength, secondSubstringLength),
        * thirdDeepVertex = new SuffixTreeVertex(firstSubstringLength + secondSubstringLength, thirdSubstringLength),
        * root = const_cast<SuffixTreeVertex *>(builder->getRoot());
    root->addChildRelation(firstDeepVertex);
    firstDeepVertex->addChildRelation(secondDeepVertex);
    secondDeepVertex->addChildRelation(thirdDeepVertex);

    int stringOverlayLength = firstSubstringLength + secondSubstringLength + 1;
    std::string suffixTreeString = getSuffixTreeBuilderString(builder), 
        stringToOverlay = suffixTreeString.substr(0, stringOverlayLength);
    auto maxDeepVertexWhileOverlayingSubstringAndRemainingSuffix = 
        goDownUntilSuffixSuperimposes(builder, root, stringToOverlay);

    assert(maxDeepVertexWhileOverlayingSubstringAndRemainingSuffix.first == secondDeepVertex);
    assert(maxDeepVertexWhileOverlayingSubstringAndRemainingSuffix.second == 
           suffixTreeString.substr(stringOverlayLength - maxDeepVertexWhileOverlayingSubstringAndRemainingSuffix.second.length(), 
                                maxDeepVertexWhileOverlayingSubstringAndRemainingSuffix.second.length()));
}

void addLeafToVertexTest() {
    SuffixTreeBuilder * builder = createHelloWorldSuffixTreeBuilder();
    std::string suffixTreeString = getSuffixTreeBuilderString(builder);
    int suffixLength = 5,  entryIndex = suffixTreeString.length() - suffixLength;
    SuffixTreeVertex * parent = new SuffixTreeVertex(0, 0);
    
    std::string suffixString = suffixTreeString.substr(entryIndex);
    SuffixTreeVertex * newLeaf = addLeafToVertex(builder, parent, suffixString);

    assert(parent->getChildren()->size() == 1);
    assert(parent->getChildren()->at(0) == newLeaf);
    assert(newLeaf->getParent() == parent);
    assert(newLeaf->getInfo().first == entryIndex && newLeaf->getInfo().second == suffixLength);
}

void goUpTheBranchesAndAddPrefixLinksIfNecessaryTest() {
    SuffixTreeBuilder * builder = createHelloWorldSuffixTreeBuilder();
    SuffixTreeVertex * firstBranchFirstVertex = new SuffixTreeVertex(0, 1),
        * firstBranchSecondVertex = new SuffixTreeVertex(1, 3),
        * secondBranchFirstVertex = new SuffixTreeVertex(0, 1),
        * secondBranchSecondVertex = new SuffixTreeVertex(1, 2),
        * secondBranchThirdVertex = new SuffixTreeVertex(3, 1),
        * root = builder->getRoot();
    root->addChildRelation(firstBranchFirstVertex);
    firstBranchFirstVertex->addChildRelation(firstBranchSecondVertex);
    root->addChildRelation(secondBranchFirstVertex);
    secondBranchFirstVertex->addChildRelation(secondBranchSecondVertex);
    secondBranchSecondVertex->addChildRelation(secondBranchThirdVertex);

    char prefixChar = 'c';
    goUpTheBranchesAndAddPrefixLinksIfNecessary(builder, secondBranchThirdVertex, firstBranchSecondVertex, prefixChar);

    assert(secondBranchFirstVertex->getPrefixLinkedVertex(prefixChar) == firstBranchFirstVertex);
    assert(secondBranchSecondVertex->getPrefixLinkedVertex(prefixChar) == nullptr);
    assert(secondBranchThirdVertex->getPrefixLinkedVertex(prefixChar) == nullptr);
    assert(firstBranchFirstVertex->getPrefixLinkedVertex(prefixChar) == nullptr);
    assert(firstBranchSecondVertex->getPrefixLinkedVertex(prefixChar) == nullptr);

}

void splitBranchWhileSuffixSuperimposesAndGetSplitPlaceVertexTest() {
    SuffixTreeBuilder * builder = createHelloWorldSuffixTreeBuilder();
    std::string suffixTreeString = getSuffixTreeBuilderString(builder);
    int substringEntryIndex = 0, substringLength = 5;
    SuffixTreeVertex * branchParent = new SuffixTreeVertex(0, 0),
        * branchChild = new SuffixTreeVertex(substringEntryIndex, substringLength);
    branchParent->addChildRelation(branchChild);
    std::string stringToSuperimpose = builder->getVertexSubstring(branchChild).substr(substringEntryIndex, substringLength - 2);

    SuffixTreeVertex * branchSplitPlace = 
        splitBranchWhileSuffixSuperimposesAndGetSplitPlaceVertex(builder, branchParent, stringToSuperimpose);

    assert(branchParent->getChildren()->size() == 1);
    assert(branchParent->getChildren()->at(0) == branchSplitPlace);
    assert(branchSplitPlace->getParent() == branchParent);
    assert(branchSplitPlace->getChildren()->size() == 1);
    assert(branchSplitPlace->getChildren()->at(0) == branchChild);
    assert(branchChild->getParent() == branchSplitPlace);
    assert(branchChild->getChildren()->size() == 0);
    assert(builder->getVertexSubstring(branchSplitPlace) + builder->getVertexSubstring(branchChild) == 
        builder->getSuffixTreeSubstring(substringEntryIndex, substringLength));
}

void forkBranchAndGetNewLeafTest() {
    SuffixTreeBuilder * builder = createHelloWorldSuffixTreeBuilder();
    std::string suffixTreeString = getSuffixTreeBuilderString(builder);
    int startLeafSubstringEntryIndex = 0, startLeafSubstringLength = 5;
    SuffixTreeVertex * startLeaf = new SuffixTreeVertex(0, startLeafSubstringLength),
        * root = builder->getRoot();
    root->addChildRelation(startLeaf);
    
    int forkLeafSubstringEntryIndex = 6, forkLeafSubstringLength = 3;
    std::string stringToSplitBranch = suffixTreeString.substr(startLeafSubstringEntryIndex, startLeafSubstringLength - 2),
        stringToForkBranch = suffixTreeString.substr(forkLeafSubstringEntryIndex, forkLeafSubstringLength);
    
    auto splitLeaf = forkBranchAndGetNewLeaf(builder, root, stringToSplitBranch),
        forkLeaf = forkBranchAndGetNewLeaf(builder, root, stringToForkBranch),
        splitPlaceVertex = splitLeaf->getParent();

    assert(root->getChildren()->size() == 2);
    assert(root->getChildren()->at(0) == forkLeaf || root->getChildren()->at(1) == forkLeaf);
    assert(root->getChildren()->at(0) == splitPlaceVertex || root->getChildren()->at(1) == splitPlaceVertex);
    assert(forkLeaf->getParent() == root);
    assert(forkLeaf->getChildren()->size() == 0);
    assert(splitPlaceVertex->getParent() == root);
    assert(splitPlaceVertex->getChildren()->size() == 2);
    assert(splitPlaceVertex->getChildren()->at(0) == splitLeaf || splitPlaceVertex->getChildren()->at(1) == splitLeaf);
    assert(splitPlaceVertex->getChildren()->at(0) == startLeaf || splitPlaceVertex->getChildren()->at(1) == startLeaf);
    assert(splitLeaf->getParent() == splitPlaceVertex);
    assert(splitLeaf->getChildren()->size() == 0);
    assert(startLeaf->getParent() == splitPlaceVertex);
    assert(startLeaf->getChildren()->size() == 0);
}

void handleNextSuffixAndGetNewLeafTest() {
    SuffixTreeBuilder * builder = new SuffixTreeBuilder("abacaba");
    std::string suffixTreeString = getSuffixTreeBuilderString(builder);
    int stringLength = suffixTreeString.length();
    SuffixTreeVertex * firstBuiltVertex = new SuffixTreeVertex(stringLength - 1, 1),
        * secondBuiltVertex = new SuffixTreeVertex(stringLength - 2, 2),
        * root = builder->getRoot();
    root->addChildRelation(firstBuiltVertex);
    root->addChildRelation(secondBuiltVertex);

    std::string thirdLeafSubstring = suffixTreeString.substr(stringLength - 3, 3),
        fourthLeafSubstring = suffixTreeString.substr(stringLength - 4, 4);
    auto thirdBuiltLeaf = handleNextSuffixAndGetNewLeaf(builder, secondBuiltVertex, thirdLeafSubstring);
    auto fourthBuiltLeaf = handleNextSuffixAndGetNewLeaf(builder, thirdBuiltLeaf, fourthLeafSubstring);
    
    assert(root->getChildren()->size() == 3);
}

void buildTest() {
    SuffixTreeBuilder * stb = new SuffixTreeBuilder("abacaba");
    
    stb->build();

    stb->printDebugView();

    delete stb;
}

SuffixTreeBuilder * createHelloWorldSuffixTreeBuilder() {
    std::string suffixTreeString = "hello_world";
    SuffixTreeBuilder * builder = new SuffixTreeBuilder(suffixTreeString);
    return builder;
}

std::string getSuffixTreeBuilderString(SuffixTreeBuilder * builder) {
    return builder->getSuffixTreeSubstring(0, builder->getTreeStringLength());
}
