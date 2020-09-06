#include <iostream>
#include "suffix_tree.hpp"
#include <string>
#include <sstream> // for std::stringstream
#include "suffix_tree_output.hpp"

void test_suffix_tree_constructor();
void test_suffix_tree_string_slice_getting();

void test_suffix_tree_vertex_info();
void test_suffix_tree_vertex_inheritance();
void test_suffix_tree_vertex_prefix_link();
void test_suffix_tree_vertex_leaf();

void test_suffix_tree_build();

void print_test_start(std::string const &test_name);
void print_test_segment(std::string const &value_name, std::string const &got, std::string const &expected);
void print_test_segment(std::string const &value_name, SuffixTreeVertex *got, SuffixTreeVertex *expected);
void print_test_segment(std::string const &value_name, int got, int expected);
void print_test_segment(std::string const &value_name, bool got, bool expected);
void print_test_end();

std::string convert_address_to_string(SuffixTreeVertex *);

int main()
{
    // test_suffix_tree_constructor();
    // test_suffix_tree_string_slice_getting();
    // test_suffix_tree_prefix_restoring();

    // test_suffix_tree_vertex_info();
    // test_suffix_tree_vertex_inheritance();
    // test_suffix_tree_vertex_prefix_link();
    // test_suffix_tree_vertex_leaf();

    test_suffix_tree_build();
    return 0;
}

void test_suffix_tree_constructor()
{
    print_test_start("suffix tree constructor");

    std::string const tree_string("flower");
    SuffixTree *st = new SuffixTree(tree_string);
    std::string tree_string_got = st->get_tree_string_slice(0, tree_string.length());
    SuffixTreeVertex *tree_root_vertex_address = st->get_root_vertex();

    print_test_segment("tree string", tree_string_got, tree_string);

    delete st;
    print_test_end();
}

void test_suffix_tree_string_slice_getting()
{
    print_test_start("suffix tree string slice");

    std::string const tree_string("flower");
    SuffixTree *st = new SuffixTree(tree_string);
    size_t i = 2, length = 4;
    std::string tree_string_slice = st->get_tree_string_slice(i, length), expected_slice = tree_string.substr(i, length);

    print_test_segment("tree string slice", tree_string_slice, expected_slice);

    delete st;
    print_test_end();
}

void test_suffix_tree_vertex_info()
{
    print_test_start("suffix tree vertex info");

    int entry = 2, length = 5;
    SuffixTreeVertex *stv = new SuffixTreeVertex(0, 0);
    stv->set_vertex_info(entry, length);
    int stv_entry_index = stv->get_string_entry_index(), stv_substring_length = stv->get_substring_length();

    print_test_segment("vertex basic info, entry index", stv_entry_index, entry);
    print_test_segment("vertex basic info, string length", stv_substring_length, length);

    delete stv;
    print_test_end();
}

void test_suffix_tree_vertex_inheritance()
{
    print_test_start("suffix tree vertex adding child");
    SuffixTreeVertex *stv_parent = new SuffixTreeVertex(0, 0);
    SuffixTreeVertex *stv_child = new SuffixTreeVertex(0, 0, stv_parent);

    print_test_segment("suffix tree vertexes' parental affiliation", stv_child->get_parent(), stv_parent);
    print_test_segment("suffix tree vertexes' baby accessories", stv_parent->get_childrens()->at(0), stv_child);

    print_test_end();
}

void test_suffix_tree_vertex_prefix_link()
{
    print_test_start("suffix tree vertex adding child");

    SuffixTreeVertex *stv_main = new SuffixTreeVertex(0, 0);
    SuffixTreeVertex *stv_prefix_linked = new SuffixTreeVertex(0, 0);
    char prefix = 'p';
    stv_main->add_prefix_link(stv_prefix_linked, prefix);

    print_test_segment("suffix tree vertex's prefix link availability", stv_main->has_prefix_link(prefix), true);
    print_test_segment("suffix tree vertex's prefix link coincidence", stv_main->get_prefix_link(prefix), stv_prefix_linked);

    print_test_end();
}

void test_suffix_tree_vertex_leaf()
{
    print_test_start("suffix tree vertex adding child");

    bool leaf_1 = false, root_1 = false;
    bool leaf_2 = true, root_2 = true;
    SuffixTreeVertex *stv_1 = new SuffixTreeVertex(0, 0, leaf_1, root_1);
    SuffixTreeVertex *stv_2 = new SuffixTreeVertex(0, 0, leaf_2, root_2);

    print_test_segment("suffix tree vertex's leaf vertex class affiliation", stv_1->is_leaf(), leaf_1);
    print_test_segment("suffix tree vertex's leaf vertex class affiliation", stv_2->is_leaf(), leaf_2);
    print_test_segment("suffix tree vertex's root vertex class affiliation", stv_1->is_root(), root_1);
    print_test_segment("suffix tree vertex's root vertex class affiliation", stv_2->is_root(), root_2);

    print_test_end();
}

void test_suffix_tree_build()
{
    print_test_start("tree suffix tree build");

    SuffixTree *st = new SuffixTree("fucuk");

    std::cout << "CHILDS: " << st->get_root_vertex()->get_childrens()->size() << std::endl;

    for (int i = 0; i < st->get_root_vertex()->get_childrens()->size(); ++i)
    {
        SuffixTreeVertex *child = st->get_root_vertex()->get_childrens()->at(i);
        int entry = child->get_string_entry_index(), len = child->get_substring_length();
        std::cout << entry << " " << len << std::endl;
        std::cout << st->get_tree_string_slice(entry, len) << std::endl;
    }

    // print_suffix_tree(st);

    delete st;

    print_test_end();
}

void print_test_start(std::string const &test_name)
{
    printf("\n-- Started test \"%s\" --\n", test_name.c_str());
}

void print_test_segment(std::string const &value_name, std::string const &got, std::string const &expected)
{
    std::string const pattern = ">> %s | Testing: %s | Got <-> Expected : %s <-> %s <<\n";
    bool status = got == expected;
    std::string const &status_s = status ? "OK " : "ERR";
    std::printf(pattern.c_str(), status_s.c_str(), value_name.c_str(), got.c_str(), expected.c_str());
    if (!status)
        throw;
}
void print_test_segment(std::string const &value_name, SuffixTreeVertex *got, SuffixTreeVertex *expected)
{
    print_test_segment(value_name, convert_address_to_string(got), convert_address_to_string(expected));
}
void print_test_segment(std::string const &value_name, int got, int expected)
{
    print_test_segment(value_name, std::to_string(got), std::to_string(expected));
}
void print_test_segment(std::string const &value_name, bool got, bool expected)
{
    print_test_segment(value_name, std::to_string(got), std::to_string(expected));
}

void print_test_end()
{
    printf("-- Finished test --\n");
}

std::string convert_address_to_string(SuffixTreeVertex *vertex)
{
    const void *address = static_cast<const void *>(vertex);
    std::stringstream ss;
    ss << address;
    return ss.str();
}
