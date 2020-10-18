#ifndef GMW_FASTA_HPP
#define GMW_FASTA_HPP

#include <string>
#include <vector>

struct FastaSequence {
    FastaSequence(std::string *description, std::string *source) : description(description), source(source) {};

    std::string *description;
    std::string *source;
};

struct FastaFileContent {
    FastaFileContent(std::string filename);

    std::vector<FastaSequence *> sequences;
private:
    std::string filename;
};

#endif
