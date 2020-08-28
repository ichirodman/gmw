#include <iostream>
#include "suffix_tree.hpp"
#include <string>

using namespace std;

#define TF "--"   // Test Framing
#define TLF ">> " // Test left framing
#define TRF " <<" // Test right framing

void test_suffix_tree_constructor();

void test_suffix_tree_string_slice_getter();

void test_suffix_tree_prefix_restoring();

int main()
{
    // test_suffix_tree_constructor();
    // test_suffix_tree_string_slice_getter();
    test_suffix_tree_prefix_restoring();
    return 0;
}

void test_suffix_tree_constructor()
{
    cout << TF << "Started test suffix tree constructor" << TF << endl;
    string const ss("flower");
    SuffixTree *st = new SuffixTree(ss);
    cout << TLF << "Tree string: " << st->get_string_tree_slice(0, ss.length()) << "                 ; Expected: " << ss << TRF << endl;
    cout << TLF << "Root vertex address: " << st->get_root() << " ; Expected: any address" << TRF << endl;
    delete st;
    cout << TF << "Finished test" << TF << endl;
}

void test_suffix_tree_string_slice_getter()
{
    cout << TF << "Started test suffix tree constructor" << TF << endl;
    string const ss("flower");
    SuffixTree *st = new SuffixTree(ss);
    size_t i = 2, length = 4;
    cout << TLF << "Tree string slice: " << st->get_string_tree_slice(i, length) << " ; Expected: " << ss.substr(i, length) << TRF << endl;
    delete st;
    cout << TF << "Finished test" << TF << endl;
}

void test_suffix_tree_prefix_restoring()
{
    cout << TF << "Started test suffix tree prefix restoring" << TF << endl;
    string const ss("prefix");
    SuffixTree *st = new SuffixTree(ss);
    SuffixTreeVertex *stv1 = new SuffixTreeVertex(0, 2, st->get_root());
    SuffixTreeVertex *stv2 = new SuffixTreeVertex(2, 2, stv1);
    SuffixTreeVertex *stv3 = new SuffixTreeVertex(4, 2, stv2);
    cout << TLF << "Tree prefix restoring: " << st->restore_prefix(stv3) << " ; Expected: " << ss << TRF << endl;
    delete st;
    cout << TF << "Finished test" << TF << endl;
}