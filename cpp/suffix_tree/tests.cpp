#include <iostream>
#include "suffix_tree.hpp"
#include <string>

using namespace std;

#define TF "--"   // Test Framing
#define TLF ">> " // Test left framing
#define TRF " <<" // Test right framing

bool test_suffix_tree_constructor();

bool test_suffix_tree_string_slice_getting();

bool test_suffix_tree_prefix_restoring();

bool test_suffix_tree_vertex_setting_info();

bool test_suffix_tree_vertex_adding_child();

bool test_suffix_tree_vertex_setting_parent();

bool test_suffix_tree_vertex_getting_parent();

bool test_suffix_tree_vertex_getting_string_entry_index();

bool test_suffix_tree_vertex_getting_substring_length();

int main()
{
    if (!test_suffix_tree_constructor())
        return 1;
    if (!test_suffix_tree_string_slice_getting())
        return 2;
    if (!test_suffix_tree_prefix_restoring())
        return 3;
    if (!test_suffix_tree_vertex_setting_info())
        return 4;
    return 0;
}

bool test_suffix_tree_constructor()
{
    cout << TF << "Started test suffix tree constructor" << TF << endl;

    string const ss("flower");
    SuffixTree *st = new SuffixTree(ss);
    string tree_string = st->get_tree_string_slice(0, ss.length());
    SuffixTreeVertex *tree_root_vertex_address = st->get_root_vertex();

    cout << TLF << "Tree string: " << tree_string << "                 ; Expected: " << ss << TRF << endl;
    cout << TLF << "Root vertex address: " << tree_root_vertex_address << " ; Expected: any address" << TRF << endl;

    delete st;
    cout << TF << "Finished test" << TF << endl
         << endl;
    return tree_string == ss && tree_root_vertex_address != nullptr;
}

bool test_suffix_tree_string_slice_getting()
{
    cout << TF << "Started test suffix tree constructor" << TF << endl;

    string const ss("flower");
    SuffixTree *st = new SuffixTree(ss);
    size_t i = 2, length = 4;
    string tree_string_slice = st->get_tree_string_slice(i, length), expected_slice = ss.substr(i, length);

    cout << TLF << "Tree string slice: " << tree_string_slice << " ; Expected: " << expected_slice << TRF << endl;

    delete st;
    cout << TF << "Finished test" << TF << endl
         << endl;
    return tree_string_slice == expected_slice;
}

bool test_suffix_tree_prefix_restoring()
{
    cout << TF << "Started test suffix tree prefix restoring" << TF << endl;

    string const ss("prefix");
    SuffixTree *st = new SuffixTree(ss);
    SuffixTreeVertex *stv1 = new SuffixTreeVertex(0, 2, st->get_root_vertex());
    SuffixTreeVertex *stv2 = new SuffixTreeVertex(2, 2, stv1);
    SuffixTreeVertex *stv3 = new SuffixTreeVertex(4, 2, stv2);
    string restored_prefix = st->restore_prefix_string(stv3);

    cout << TLF << "Tree prefix restoring: " << restored_prefix << " ; Expected: " << ss << TRF << endl;

    delete st;
    cout << TF << "Finished test" << TF << endl
         << endl;
    return restored_prefix == ss;
}

bool test_suffix_tree_vertex_setting_info()
{
    cout << TF << "Started test suffix tree prefix restoring" << TF << endl;

    int entry = 2, length = 5;
    SuffixTreeVertex *stv = new SuffixTreeVertex(0, 0);
    stv->set_vertex_info(entry, length);
    int stv_entry_index = stv->get_string_entry_index(), stv_substring_length = stv->get_substring_length();

    cout << TLF << "Tree vertex basic info: " << stv_entry_index << ", " << stv_substring_length << " ; Expected: " << entry << ", " << length << endl;

    delete stv;
    cout << TF << "Finished test" << TF << endl
         << endl;
    return stv_entry_index == entry && stv_substring_length == length;
}