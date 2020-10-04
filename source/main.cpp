#include "utils/fasta.hpp"
#include "utils/code_timing.hpp"
#include "suffix_tree/builder/suffix_tree_builder.hpp"
#include <iostream>


int main() {
    std::string filename = "large1/large_genome1.fasta";
    FastaFileContent * ffc = new FastaFileContent(filename);
    std::string sequence = ffc->sequences.at(0)->source->substr(0, 125000);
    // SuffixTreeBuilder * builder = new SuffixTreeBuilder(sequence);
    SuffixTreeBuilder * builder = new SuffixTreeBuilder("abbacabaa");
    // startTiming();
    builder->build();
    // finishTiming();
    builder->printDebugView();
    return 0;
}
