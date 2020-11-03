#include "utils/fasta.hpp"
#include "utils/code_timing.hpp"
#include "slice_matcher/approximate/approximate_slice_matcher.hpp"
#include "slice_matcher/approximate/approximate_slice_matches_file_formatter.hpp"


int main() {
    startTiming();
    auto *firstFastaFile = new FastaFileContent("large2/large_genome1.fasta"),
            *secondFastaFile = new FastaFileContent("large2/large_genome2.fasta");
    auto sliceMatcher = new GlobalApproximateSliceMatcher(firstFastaFile->sequences.at(0),
                                                          secondFastaFile->sequences.at(0));
    auto fileFormatter = new ApproximateSliceMatchesFileFormat("fuck_you.txt");
    fileFormatter->write(sliceMatcher);
    finishTiming();
    return 0;
}
