#include <string>
#include <iostream>
#include "utils/fasta.hpp"
#include "algos/simple_dust.hpp"

using namespace std;

int main()
{
    string first_filepath("large1/large_genome1.fasta");
    FastaFileContent *seqs = new FastaFileContent(first_filepath);
    // cout << seqs->sequences[0]->source << endl;
    dust(seqs->sequences[0]);
    // cout << seqs->sequences[0]->source << endl;
    return 0;
}