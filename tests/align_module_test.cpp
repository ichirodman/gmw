#include "../src/utils/code_timing.hpp"
#include "../src/approximate_aligner/approximate_aligner.hpp"


int main() {
    startTiming();

    std::string firstFilename = "large1/large_genome2.fasta", secondFilename = "large1/large_genome1.fasta";
    ApproximateAligner *aligner = new ApproximateAligner(firstFilename, secondFilename, 100);
    aligner->align();

    delete aligner;
    finishTiming();

    return 0;
}
