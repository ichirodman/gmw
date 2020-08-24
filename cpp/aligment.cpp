#include <string>
#include <iostream>
#include "utils/fasta.hpp"
#include "algos/simple_dust.hpp"
#include "sdust/sdust.h"

using namespace std;

int main()
{
    string first_filepath("large1/large_genome1.fasta");
    FastaFileContent *seqs = new FastaFileContent(first_filepath);
    dust(seqs->sequences[0]);
    return 0;
}