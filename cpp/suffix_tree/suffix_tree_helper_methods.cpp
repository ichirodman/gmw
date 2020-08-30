#include "suffix_tree.hpp"
#include <iostream>
#include <vector>

SuffixTreeVertex::SuffixTreeVertex(int string_entry_index, int substring_length, bool is_leaf, bool is_root)
    : string_entry_index(string_entry_index), substring_length(substring_length), leaf(is_leaf), root(is_root)
{
    this->children = new std::vector<SuffixTreeVertex *>();
    this->prefix_links = new std::vector<SuffixTreeVertex *>();
    this->prefix_chars = new std::vector<char>();
    this->parent = nullptr;
};

SuffixTreeVertex::SuffixTreeVertex(int string_entry_index, int substring_length, SuffixTreeVertex *parent, bool is_leaf, bool is_root)
    : SuffixTreeVertex(string_entry_index, substring_length, is_leaf, is_root) { this->set_parent(parent); };

SuffixTreeVertex::~SuffixTreeVertex()
{
    delete this->children;
    delete this->prefix_links;
    delete this->prefix_chars;
    delete this->parent;
}

void SuffixTreeVertex::set_vertex_info(int string_entry_index, int substring_length)
{
    this->string_entry_index = string_entry_index;
    this->substring_length = substring_length;
}

int SuffixTreeVertex::get_string_entry_index() { return this->string_entry_index; }

int SuffixTreeVertex::get_substring_length() { return this->substring_length; }

void SuffixTreeVertex::add_child(SuffixTreeVertex *child) { this->children->push_back(child); }

std::vector<SuffixTreeVertex *> *SuffixTreeVertex::get_childrens() { return this->children; }

void SuffixTreeVertex::set_parent(SuffixTreeVertex *parent)
{
    this->parent = parent;
    parent->add_child(this);
}

SuffixTreeVertex *SuffixTreeVertex::get_parent() { return this->parent; }

void SuffixTreeVertex::add_prefix_link(SuffixTreeVertex *prefix_link, char prefix_char)
{
    this->prefix_links->push_back(prefix_link);
    this->prefix_chars->push_back(prefix_char);
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

int SuffixTreeVertex::if_leaf_get_entry_index() { return this->leaf ? this->string_entry_index : -1; };

bool SuffixTreeVertex::is_root() { return this->root; }

SuffixTree::SuffixTree(const std::string &tree_string)
    : tree_string(tree_string)
{
    this->root_vertex = new SuffixTreeVertex(0, 0, false, true);
    this->build(tree_string);
};

SuffixTree::~SuffixTree() { delete this->root_vertex; }

std::string SuffixTree::get_tree_string_slice(int start_index, int length) { return this->tree_string.substr(start_index, length); }

std::string SuffixTree::restore_prefix_string(SuffixTreeVertex *prefix_end)
{
    std::string prefix_string("");
    for (SuffixTreeVertex *vertex = prefix_end; !(vertex->is_root()); vertex = vertex->get_parent())
    {
        std::string vertex_substring = this->get_tree_string_slice(vertex->get_string_entry_index(), vertex->get_substring_length());
        prefix_string = vertex_substring + prefix_string;
    }
    return prefix_string;
}

SuffixTreeVertex *SuffixTree::get_root_vertex() { return this->root_vertex; }
