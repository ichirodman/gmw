#ifndef SUFFIX_TREE
#define SUFFIX_TREE

#include <vector>
#include <string>

#define END_CHAR '$' // Non-alphabetic suffixes end char

class SuffixTree;

class SuffixTreeVertex final
{
public:
    SuffixTreeVertex(int entry_index, int length, bool leaf = false, bool root = false);
    SuffixTreeVertex(int entry_index, int length, SuffixTreeVertex *parent, bool leaf = false, bool root = false);
    ~SuffixTreeVertex();

    void set_vertex_info(int, int);

    int get_string_entry_index();
    int get_substring_length();

    bool has_child(SuffixTreeVertex *);
    void add_child(SuffixTreeVertex *);
    void remove_child(SuffixTreeVertex *);
    std::vector<SuffixTreeVertex *> *get_childrens();

    void set_parent(SuffixTreeVertex *);
    SuffixTreeVertex *get_parent();

    void add_prefix_link(SuffixTreeVertex *, char);
    bool has_prefix_link(char);
    SuffixTreeVertex *get_prefix_link(char);

    bool is_leaf();
    int if_leaf_get_suffix_entry_index();

    bool is_root();

private:
    std::vector<SuffixTreeVertex *> *children;
    std::vector<SuffixTreeVertex *> *prefix_links;
    std::vector<char> *prefix_chars;
    SuffixTreeVertex *parent;
    int string_entry_index, substring_length;
    bool leaf, root;
};

class SuffixTree final
{
public:
    explicit SuffixTree(const std::string &);
    ~SuffixTree();

    std::string restore_prefix_string(SuffixTreeVertex *);

    std::string get_vertex_substring(SuffixTreeVertex *);

    std::string get_tree_string_slice(int, int);

    SuffixTreeVertex *get_root_vertex();

    int get_tree_string_length();

    SuffixTreeVertex *get_leaf_by_suffix(std::string &);
    bool has_this_suffix(std::string &);

private:
    void build(const std::string &);

    SuffixTreeVertex *root_vertex;
    const std::string &tree_string;
};

#endif