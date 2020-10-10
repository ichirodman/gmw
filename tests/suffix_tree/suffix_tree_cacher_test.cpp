#include "../../source/suffix_tree/cacher.hpp"
#include <assert.h>


void cacheSuffixTreeTest();

int main() {
    cacheSuffixTreeTest();
    return 0;
}

void cacheSuffixTreeTest() {
    SuffixTree * st = new SuffixTree("abacaba");
    SuffixTreeCacher * stc = new SuffixTreeCacher();

    stc->cache(st, "cacher_test", 0);

    delete st, stc;
}
