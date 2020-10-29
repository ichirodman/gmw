#include "utils/fasta.hpp"
#include "utils/code_timing.hpp"
#include "suffix_forest/suffix_forest.hpp"

int main() {
    std::string filename = "large1/large_genome1.fasta";
    auto *ffc = new FastaFileContent(filename);
    FastaSequence *fastaSequence = ffc->sequences.at(0);
    startTiming();
    auto *suffixForest = new SuffixForest(fastaSequence);
    suffixForest->build();
    finishTiming();
    return 0;
}
