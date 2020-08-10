#include "fasta.hpp"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string filename("CP000766.3.fasta");
    FastaFileContent *ffc = new FastaFileContent(filename);
    cout << ffc->sequences[0]->description << endl;
    cout << ffc->sequences[0]->source.length() << endl;
    return 0;
}