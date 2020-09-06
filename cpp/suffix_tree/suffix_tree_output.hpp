#ifndef SUFFIX_TREE_OUTPUT
#define SUFFIX_TREE_OUTPUT

#include <iostream>
#include "suffix_tree.hpp"

std::string go_down(SuffixTree *suffix_tree, SuffixTreeVertex *vertex, int deep)
{
    std::string tree_string_representation = "|";
    for (int i = 0; i < deep; ++i)
    {
        tree_string_representation += "  ";
    }
    tree_string_representation += "+-";
    // std::cout << "VERTEX SUB: " << suffix_tree->get_tree_string_slice(vertex->get_string_entry_index(), vertex->get_substring_length()) << ":" << std::endl;
    tree_string_representation += suffix_tree->get_vertex_substring(vertex);
    tree_string_representation += '\n';

    if (!vertex->is_leaf())
    {
        for (int i = 0; i < vertex->get_childrens()->size(); ++i)
        {
            tree_string_representation += go_down(suffix_tree, vertex->get_childrens()->at(i), deep + 1);
        }
    }
    // else
    // {
    //     std::cout << std::endl
    //               << "FFF: " << vertex->get_string_entry_index() << " - " << vertex->get_substring_length() << std::endl;
    // }
    return tree_string_representation;
}

void print_suffix_tree(SuffixTree *suffix_tree)
{
    using std::cout;
    using std::endl;
    using std::string;

    string tree_string_representation = go_down(suffix_tree, suffix_tree->get_root_vertex(), 1);
    cout << tree_string_representation << endl;
}

#endif