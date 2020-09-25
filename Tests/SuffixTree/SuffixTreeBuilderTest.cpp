#include "../../Source/SuffixTree/SuffixTree.hpp"
#include <assert.h>
#include <iostream>


void getRootTest();

void getVertexSubstringTest();

void buildTest();

int main() {
    getRootTest();
    getVertexSubstringTest();
    // buildTest();
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

void buildTest() {
    SuffixTreeBuilder * stb = new SuffixTreeBuilder("hello_world");
    
    stb->build();

    delete stb;
}
