//
// Created by ichigo on 22.02.2021.
//

#ifndef GMW_APPROXIMATE_ALIGNER_HPP
#define GMW_APPROXIMATE_ALIGNER_HPP


#include "./slice_matcher/approximate_slice_matcher.hpp"
#include "./slice_matcher/approximate_slice_matches_file_formatter.hpp"
#include "../utils/fasta.hpp"

#define filenameWillAutogenerate "will autogenerate while init"


class ApproximateAligner {
public:
    ApproximateAligner(const std::string &, const std::string &, const std::string & = filenameWillAutogenerate,
                       int = 200, int = 0, int = 0);

    ApproximateAligner(const std::string &, const std::string &, int);

    ~ApproximateAligner();

    void align();

private:
    const std::string querySequenceFilename, targetSequenceFilename, outputFilename;

    const int sliceMatchSize, querySequenceFileIndex, targetSequenceFileIndex;
};


#endif //GMW_APPROXIMATE_ALIGNER_HPP
