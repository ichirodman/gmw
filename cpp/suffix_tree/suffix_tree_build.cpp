#include "suffix_tree.hpp"
#include <iostream>

std::string get_suffix_string(const std::string &tree_string, int suffix_length)
{
    return tree_string.substr(tree_string.length() - suffix_length, suffix_length);
}

void add_prefix_link(SuffixTreeVertex *vertex_without_prefix, SuffixTreeVertex *vertex_with_prefix, char prefix)
{
    vertex_without_prefix->add_prefix_link(vertex_with_prefix, prefix);
}

std::pair<SuffixTreeVertex *, std::string> go_up_for_vertex_with_prefix_link(SuffixTree *suffix_tree, SuffixTreeVertex *vertex, char prefix_char)
{
    std::string suffix_remainder = "";
    for (; !vertex->has_prefix_link(prefix_char); vertex = vertex->get_parent())
    {
        std::cout << "HERE" << std::endl;
        suffix_remainder.insert(0, suffix_tree->get_vertex_substring(vertex));
    }
    return std::pair<SuffixTreeVertex *, std::string>(vertex, suffix_remainder);
}

SuffixTreeVertex *get_child_with_prefix_link(SuffixTreeVertex *vertex, char prefix)
{
    for (int i = 0; i < vertex->get_childrens()->size(); ++i)
    {
        SuffixTreeVertex *child = vertex->get_childrens()->at(i);
        if (child->has_prefix_link(prefix))
        {
            return child;
        }
    }
    return nullptr;
}

SuffixTreeVertex *get_child_with_matching_substring_prefix(SuffixTree *suffix_tree, SuffixTreeVertex *vertex, char prefix)
{
    for (int i = 0; i < vertex->get_childrens()->size(); ++i)
    {
        SuffixTreeVertex *child = vertex->get_childrens()->at(i);
        if (suffix_tree->get_vertex_substring(child).at(0) == prefix)
        {
            return child;
        }
    }
    return nullptr;
}
std::pair<SuffixTreeVertex *, std::string> go_down_while_suffix_remainder_superimposes(SuffixTree *suffix_tree, SuffixTreeVertex *vertex, std::string suffix_remainder)
{
    while (true)
    {
        SuffixTreeVertex *child_to_follow = get_child_with_matching_substring_prefix(suffix_tree, vertex, suffix_remainder.at(0));
        if (child_to_follow == nullptr)
        {
            break;
        }
        else
        {
            std::string child_substring = suffix_tree->get_vertex_substring(child_to_follow);
            if (child_substring.length() < suffix_remainder.length())
            {
                break;
            }
            else
            {
                if (child_substring != suffix_remainder.substr(0, child_substring.length()))
                {
                    break;
                }
                else
                {
                    suffix_remainder = suffix_remainder.substr(child_substring.length(), suffix_remainder.length() - child_substring.length());
                }
            }
        }
    }
    return std::pair<SuffixTreeVertex *, std::string>(vertex, suffix_remainder);
}

bool possible_to_split_any_branch(SuffixTree *suffix_tree, SuffixTreeVertex *parent, std::string suffix_remainder)
{
    return get_child_with_matching_substring_prefix(suffix_tree, parent, suffix_remainder.at(0)) != nullptr;
}

SuffixTreeVertex *add_leaf_with_remainer(SuffixTree *suffix_tree, SuffixTreeVertex *parent, std::string suffix_remainder)
{
    int tree_string_entry_index = suffix_tree->get_tree_string_length() - suffix_remainder.length();
    SuffixTreeVertex *new_child = new SuffixTreeVertex(tree_string_entry_index, suffix_remainder.length(), true);
    parent->add_child(new_child);
    new_child->set_parent(parent);
    return new_child;
}

SuffixTreeVertex *split_new_branch(SuffixTree *suffix_tree, SuffixTreeVertex *branch_parent, std::string suffix_remainder)
{
    SuffixTreeVertex *branch_child = get_child_with_matching_substring_prefix(suffix_tree, branch_parent, suffix_remainder.at(0));
    std::string branch_substring = suffix_tree->get_vertex_substring(branch_child);

    int match_length = 0;
    for (; suffix_remainder.at(match_length) == branch_substring.at(match_length); match_length++)
        ;
    std::cout << suffix_remainder << " | " << branch_substring << std::endl;

    std::cout << "Match length: " << match_length << std::endl;

    SuffixTreeVertex *split_branch_child =
        new SuffixTreeVertex(branch_child->get_string_entry_index(), match_length);
    std::cout << "Split branch child substring: " << suffix_tree->get_vertex_substring(split_branch_child) << std::endl;
    branch_child->set_vertex_info(branch_child->get_string_entry_index() + match_length, branch_child->get_substring_length() - match_length);
    branch_parent->remove_child(branch_child);
    split_branch_child->add_child(branch_child);
    branch_parent->add_child(split_branch_child);
    branch_child->set_parent(split_branch_child);
    split_branch_child->set_parent(branch_child);

    int new_split_branch_leaf_substring_length = suffix_remainder.length() - match_length;
    int new_split_brach_leaf_string_entry_index = suffix_tree->get_tree_string_length() - new_split_branch_leaf_substring_length;
    SuffixTreeVertex *new_split_branch_leaf =
        new SuffixTreeVertex(new_split_brach_leaf_string_entry_index, new_split_branch_leaf_substring_length, true);

    std::cout << "New leaf entry: " << new_split_brach_leaf_string_entry_index << "  length: " << new_split_branch_leaf_substring_length << std::endl;
    std::cout << "Leaf substring: " << suffix_tree->get_vertex_substring(new_split_branch_leaf) << std::endl;
    split_branch_child->add_child(new_split_branch_leaf);
    new_split_branch_leaf->set_parent(split_branch_child);

    return new_split_branch_leaf;
}

void SuffixTree::build(const std::string &tree_string)
{
    using std::string;

    SuffixTreeVertex *current_vertex = this->get_root_vertex();
    for (int suffix_length = 1; suffix_length <= tree_string.length(); ++suffix_length)
    {
        string suffix_string = get_suffix_string(tree_string, suffix_length);
        char suffix_prefix = suffix_string.at(0);
        std::cout << "New suffix: " << suffix_string << std::endl;

        std::pair<SuffixTreeVertex *, std::string> previous_leaf_vertex_with_prefix_link_and_suffix_remainder =
            go_up_for_vertex_with_prefix_link(this, current_vertex, suffix_string.at(0));
        SuffixTreeVertex *next_leaf_prefix_linked_vertex = previous_leaf_vertex_with_prefix_link_and_suffix_remainder.first->get_prefix_link(suffix_prefix);
        std::string suffix_remainder = next_leaf_prefix_linked_vertex->is_root() ? suffix_string
                                                                                 : previous_leaf_vertex_with_prefix_link_and_suffix_remainder.second;

        std::cout << "Suffix remainder: " << suffix_remainder << std::endl;
        std::pair<SuffixTreeVertex *, std::string> next_leaf_max_deep_vertex_and_suffix_remainder =
            go_down_while_suffix_remainder_superimposes(this, next_leaf_prefix_linked_vertex, suffix_remainder);
        SuffixTreeVertex *next_leaf_closest_to_split_place_vertex = next_leaf_max_deep_vertex_and_suffix_remainder.first;
        suffix_remainder = next_leaf_max_deep_vertex_and_suffix_remainder.second;

        SuffixTreeVertex *new_leaf = nullptr;
        if (possible_to_split_any_branch(this, next_leaf_closest_to_split_place_vertex, suffix_remainder))
        {
            new_leaf = split_new_branch(this, next_leaf_closest_to_split_place_vertex, suffix_remainder);
            std::cout << "SPLITTED" << std::endl;
            std::string previous_suffix = suffix_string.substr(1, suffix_string.length() - 1);
            if (this->has_this_suffix(previous_suffix))
            {
                SuffixTreeVertex *split_place = new_leaf->get_parent();
                this->get_leaf_by_suffix(previous_suffix)->add_prefix_link(split_place, suffix_prefix);
            }
        }
        else
        {
            new_leaf = add_leaf_with_remainer(this, next_leaf_closest_to_split_place_vertex, suffix_remainder);
        }

        previous_leaf_vertex_with_prefix_link_and_suffix_remainder.first->add_prefix_link(new_leaf, suffix_prefix);
    }
}