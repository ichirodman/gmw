#ifndef SUFFIX_TREE
#define SUFFIX_TREE

#include <vector>
#include <string>

class SuffixTreeVertex final
{
public:
    SuffixTreeVertex(int entry_index, int length, bool leaf = false, bool root = false);
    SuffixTreeVertex(int entry_index, int length, SuffixTreeVertex *parent, bool leaf = false, bool root = false);
    ~SuffixTreeVertex();

    void set_vertex_info(int, int);

    void add_child(SuffixTreeVertex *);

    void set_parent(SuffixTreeVertex *);
    SuffixTreeVertex *get_parent();

    int get_entry_index();
    int get_length();

    void add_prefix_link(SuffixTreeVertex *, char);
    bool has_prefix_link(char);
    SuffixTreeVertex *get_prefix_link(char);

    bool is_leaf();
    int if_leaf_get_entry_index();

    bool is_root();

private:
    std::vector<SuffixTreeVertex *> *children;
    std::vector<SuffixTreeVertex *> *prefix_links;
    std::vector<char> *prefix_chars;
    SuffixTreeVertex *parent;
    int entry_index, length;
    bool leaf, root;
};

class SuffixTree final
{
public:
    SuffixTree(const std::string &);
    ~SuffixTree();

    void build(const std::string &);

    std::string get_string_tree_slice(int, int);

    std::string restore_prefix(SuffixTreeVertex *);

    SuffixTreeVertex *get_root();

private:
    SuffixTreeVertex *root;
    const std::string &string_tree;
};

#endif