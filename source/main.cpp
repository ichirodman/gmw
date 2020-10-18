#include "utils/fasta.hpp"
#include "utils/code_timing.hpp"
#include "suffix_forest/suffix_forest.hpp"

int main() {
    std::string filename = "small/source.fasta";
    auto *ffc = new FastaFileContent(filename);
    FastaSequence *fastaSequence = ffc->sequences.at(0);
    startTiming();
    auto *suffixTree = new SuffixForest(fastaSequence);
    suffixTree->build();
    finishTiming();
    return 0;
}
