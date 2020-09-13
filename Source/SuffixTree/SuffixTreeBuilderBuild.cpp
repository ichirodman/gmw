#include "SuffixTree.h"
#include <assert.h>
#include <string>
#include <iostream>


void handleNextSuffix(SuffixTreeBuilder *, std::string);

void SuffixTreeBuilder::build() {
    for (int i = 1, stringLength = this->suffixTreeString.length(); i <= stringLength; ++i) {
        std::string nextSuffix = this->getSuffixTreeSubstring(stringLength - i, i);
        handleNextSuffix(this, nextSuffix);
    }
}

void handleNextSuffix(SuffixTreeBuilder * builder, std::string nextSuffix) {
    std::cout << nextSuffix << std::endl;
}
