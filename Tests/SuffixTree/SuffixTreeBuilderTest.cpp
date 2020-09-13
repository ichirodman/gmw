#include "../../Source/SuffixTree/SuffixTree.h"
#include <assert.h>
#include <iostream>


namespace tests {

    void getRootTest();

    void getVertexSubstringTest();

    void buildTest();

}

int main() {
    tests::getRootTest();
    tests::getVertexSubstringTest();
    tests::buildTest();
    return 0;
}

namespace tests {

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

        assert(stb->getVertexSubstring(stv1) == sts.substr(ei1, sl1));
        assert(stb->getVertexSubstring(stv2) == sts.substr(ei2, sl2));
        assert(stb->getVertexSubstring(stv3) == sts.substr(ei3, sl3));

        delete stb;
        delete stv1, stv2, stv3;
    }

    void buildTest() {
        SuffixTreeBuilder * stb = new SuffixTreeBuilder("hello world");
        
        stb->build();

        delete stb;
    }

}
