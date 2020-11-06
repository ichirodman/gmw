#include "utils/fasta.hpp"
#include "utils/code_timing.hpp"
#include "slice_matcher/approximate/approximate_slice_matcher.hpp"
#include "slice_matcher/approximate/approximate_slice_matches_file_formatter.hpp"


int main() {
    startTiming();
    auto *firstFastaFile = new FastaFileContent("large5/large_genome2.fasta"),
            *secondFastaFile = new FastaFileContent("large5/large_genome1.fasta");
    auto sliceMatcher = new GlobalApproximateSliceMatcher(firstFastaFile->sequences.at(0),
                                                          secondFastaFile->sequences.at(0),
                                                          25);
    auto fileFormatter = new ApproximateSliceMatchesFileFormat("large5_25.txt");
    fileFormatter->write(sliceMatcher);
    delete sliceMatcher;
    delete fileFormatter;
    delete firstFastaFile;
    delete secondFastaFile;
    finishTiming();
    return 0;
}
