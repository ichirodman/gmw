#include "suffix_tree.hpp"
#include <iostream>
#include <vector>

SuffixTreeVertex::SuffixTreeVertex(int entry_index, int length, bool leaf, bool root)
    : entry_index(entry_index), length(length), leaf(leaf), root(root)
{
    this->children = new std::vector<SuffixTreeVertex *>();
    this->prefix_links = new std::vector<SuffixTreeVertex *>();
    this->prefix_chars = new std::vector<char>();
};

SuffixTreeVertex::~SuffixTreeVertex()
{
    delete[] this->children;
    delete[] this->prefix_links;
    delete[] this->prefix_chars;
    delete this->parent;
}
void SuffixTreeVertex::set_vertex_info(int new_entry_index, int new_length)
{
    this->entry_index = new_entry_index;
    this->length = new_length;
}

void SuffixTreeVertex::add_child(SuffixTreeVertex *child) { this->children->push_back(child); }

void SuffixTreeVertex::set_parent(SuffixTreeVertex *parent) { this->parent = parent; }

SuffixTreeVertex *SuffixTreeVertex::get_parent() { return this->parent; }

int SuffixTreeVertex::get_entry_index() { return this->entry_index; }

int SuffixTreeVertex::get_length() { return this->length; }

void SuffixTreeVertex::add_prefix_link(SuffixTreeVertex *new_prefix_link, char new_prefix_char)
{
    this->prefix_links->push_back(new_prefix_link);
    this->prefix_chars->push_back(new_prefix_char);
}

bool SuffixTreeVertex::has_prefix_link(char prefix_char)
{
    for (size_t i = 0; i < this->prefix_chars->size(); ++i)
    {
        if (prefix_char == this->prefix_chars->at(i))
        {
            return true;
        }
    }
    return false;
}

SuffixTreeVertex *SuffixTreeVertex::get_prefix_link(char prefix_char)
{
    for (size_t i = 0; i < this->prefix_chars->size(); ++i)
    {
        if (this->prefix_chars->at(i) == prefix_char)
        {
            return this->prefix_links->at(i);
        }
    }
    return nullptr;
};

bool SuffixTreeVertex::is_leaf() { return this->leaf; }

int SuffixTreeVertex::if_leaf_get_entry_index() { return this->leaf ? this->entry_index : -1; };

bool SuffixTreeVertex::is_root() { return this->root; }

SuffixTree::SuffixTree(const std::string &string_tree)
    : string_tree(string_tree)
{
    this->root = new SuffixTreeVertex(0, 0, false, true);
    this->build(string_tree);
};

SuffixTree::~SuffixTree() { delete[] this->root; }

std::string SuffixTree::get_string_tree_slice(int start_index, int length) { return this->string_tree.substr(start_index, length); }

std::string SuffixTree::restore_prefix(SuffixTreeVertex *prefix_end)
{
    std::string prefix_string("");
    for (; !prefix_end->is_root(); prefix_end = prefix_end->get_parent())
    {
        std::string vertex_substring = this->get_string_tree_slice(
            prefix_end->get_entry_index(), prefix_end->get_length());
        prefix_string = vertex_substring + prefix_string;
    }
    return prefix_string;
}
