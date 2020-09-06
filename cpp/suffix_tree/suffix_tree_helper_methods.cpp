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

bool has_child(SuffixTreeVertex *child_to_check)
{
    for (int i = 0; i < child_to_check->get_childrens()->size(); ++i)
    {
        SuffixTreeVertex *child = child_to_check->get_childrens()->at(i);
        if (child == child_to_check)
        {
            return true;
        }
    }
    return false;
}

void SuffixTreeVertex::add_child(SuffixTreeVertex *child)
{
    if (this->has_child(child))
    {
        this->children->push_back(child);
    }
}

void SuffixTreeVertex::remove_child(SuffixTreeVertex *child_to_remove)
{
    for (size_t i = 0; i < this->get_childrens()->size(); ++i)
    {
        SuffixTreeVertex *child = this->get_childrens()->at(i);
        if (child == child_to_remove)
        {
            this->get_childrens()->erase(this->get_childrens()->begin() + i);
            break;
        }
    }
}

std::vector<SuffixTreeVertex *> *SuffixTreeVertex::get_childrens() { return this->children; }

void SuffixTreeVertex::set_parent(SuffixTreeVertex *parent) { this->parent = parent; }

SuffixTreeVertex *SuffixTreeVertex::get_parent() { return this->parent; }

void SuffixTreeVertex::add_prefix_link(SuffixTreeVertex *prefix_link, char prefix_char)
{
    if (!this->has_prefix_link(prefix_char))
    {
        this->prefix_links->push_back(prefix_link);
        this->prefix_chars->push_back(prefix_char);
    }
}

bool SuffixTreeVertex::has_prefix_link(char prefix_char)
{
    if (this->is_root())
    {
        return true;
    }
    else
    {
        for (int i = 0; i < this->prefix_chars->size(); ++i)
        {
            if (prefix_char == this->prefix_chars->at(i))
            {
                return true;
            }
        }
        return false;
    }
}

SuffixTreeVertex *SuffixTreeVertex::get_prefix_link(char prefix_char)
{
    if (this->is_root())
    {
        return this;
    }
    else
    {
        for (size_t i = 0; i < this->prefix_chars->size(); ++i)
        {
            if (this->prefix_chars->at(i) == prefix_char)
            {
                return this->prefix_links->at(i);
            }
        }
        return nullptr;
    }
};

bool SuffixTreeVertex::is_leaf() { return this->leaf; }

int SuffixTreeVertex::if_leaf_get_suffix_entry_index() { return this->leaf ? this->string_entry_index : -1; };

bool SuffixTreeVertex::is_root() { return this->root; }

SuffixTree::SuffixTree(const std::string &tree_string)
    : tree_string(tree_string + END_CHAR)
{
    this->root_vertex = new SuffixTreeVertex(0, 0, false, true);
    this->build(this->tree_string);
};

SuffixTree::~SuffixTree() { delete this->root_vertex; }

std::string SuffixTree::get_vertex_substring(SuffixTreeVertex *vertex)
{
    return this->get_tree_string_slice(vertex->get_string_entry_index(), vertex->get_substring_length());
}

std::string SuffixTree::get_tree_string_slice(int start_index, int length) { return this->tree_string.substr(start_index, length); }

SuffixTreeVertex *SuffixTree::get_root_vertex() { return this->root_vertex; }

int SuffixTree::get_tree_string_length() { return this->tree_string.length(); }

SuffixTreeVertex *SuffixTree::get_leaf_by_suffix(std::string &suffix_to_find)
{
    SuffixTreeVertex *vertex = this->get_root_vertex();
    while (suffix_to_find.length() > 0)
    {
        SuffixTreeVertex *appropriate_child = nullptr;
        for (int i = 0; i < vertex->get_childrens()->size(); ++i)
        {
            SuffixTreeVertex *child = vertex->get_childrens()->at(i);
            std::string child_substring = this->get_vertex_substring(child);
            if (child_substring == suffix_to_find.substr(0, child_substring.length()))
            {
                appropriate_child = child;
                break;
            }
        }
        if (appropriate_child == nullptr)
        {
            vertex = nullptr;
            break;
        }
        else
        {
            vertex = appropriate_child;
            int child_substring_len = this->get_vertex_substring(appropriate_child).length();
            suffix_to_find = suffix_to_find.substr(child_substring_len, suffix_to_find.length() - child_substring_len);
        }
    }
    return vertex;
}

bool SuffixTree::has_this_suffix(std::string &suffix)
{
    return this->get_leaf_by_suffix(suffix) != nullptr;
}