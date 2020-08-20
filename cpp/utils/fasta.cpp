#include "fasta.hpp"
#include <fstream>
#include <iostream>

FastaFileContent::FastaFileContent(std::string &filename) : filename(filename)
{
    std::string line;
    std::ifstream in("../data/" + filename);
    std::string *last_read_seq, *last_read_descriprion;
    if (in.is_open())
    {
        while (getline(in, line))
        {
            if (line.find('>') != std::string::npos)
            {
                delete last_read_seq, last_read_descriprion;
                last_read_seq = new std::string("");
                last_read_descriprion = new std::string("");
                *last_read_descriprion = line;
                sequences.push_back(new FastaSequence(*last_read_descriprion, *last_read_seq));
            }
            else
            {
                *last_read_seq += line;
            }
        }
    }
    else
    {
        std::cerr << "File not found";
    }
    in.close();
}