#include "utils/fasta.hpp"
#include "utils/code_timing.hpp"
#include "suffix_tree/builder/suffix_tree_builder.hpp"
#include <iostream>


int main() {
    std::string filename = "large1/large_genome1.fasta";
    FastaFileContent * ffc = new FastaFileContent(filename);
    std::string * sequence = ffc->sequences.at(0)->source;
    startTiming();
    for (int i = 0, slice_len = 10000; i * slice_len < sequence->length(); ++i) {
        int t = sequence->length() - i * slice_len;
        std::string slice = sequence->substr(i * slice_len, t < slice_len ? t : slice_len);
        SuffixTreeBuilder * builder = new SuffixTreeBuilder(slice);
        builder->build();
        delete builder;
        std::cout << "DONE : " << i + 1 << std::endl;
    }
    finishTiming();
    return 0;
}
