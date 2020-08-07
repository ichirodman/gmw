#pragma once
#include <string>
#include <vector>

struct FastaFileContent {
    FastaFileContent(std::string& description, std::string& source)
    {
        //TODO
    };

    struct FastaSequence {
        FastaSequence(std::string& description, std::string& source) :
            description(description), source(source) {};

        std::string& description;
        std::string& source;
    };

    std::vector<FastaSequence const*> sequences;
};
