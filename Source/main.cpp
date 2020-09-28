#include "Utils/Fasta.h"
#include "Utils/CodeTiming.hpp"
#include "SuffixTree/SuffixTreeBuilder/SuffixTreeBuilder.hpp"
#include <iostream>


int main() {
    std::string filename = "large1/large_genome1.fasta";
    FastaFileContent * ffc = new FastaFileContent(filename);
    std::string sequence = ffc->sequences.at(0)->source->substr(0, 125000);
    SuffixTreeBuilder * builder = new SuffixTreeBuilder(sequence);
    startTiming();
    builder->build();
    finishTiming();
    // builder->printDebugView();
    return 0;
}
