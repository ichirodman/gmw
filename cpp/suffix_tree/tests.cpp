#include <iostream>
#include "suffix_tree.hpp"
#include <string>

using namespace std;

int main()
{
    string const ss("flower");
    SuffixTree *st = new SuffixTree(ss);
    return 0;
}