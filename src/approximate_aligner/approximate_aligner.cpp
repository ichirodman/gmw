//
// Created by ichigo on 22.02.2021.
//

#include "approximate_aligner.hpp"


std::string generateOutputFilename(const std::string &, const std::string &, int);

ApproximateAligner::ApproximateAligner(
        const std::string &querySequenceFilename, const std::string &targetSequenceFilename,
        const std::string &outputFilename, int sliceMatchSize, int querySequenceFileIndex, int targetSequenceFileIndex)
        : querySequenceFilename(querySequenceFilename), targetSequenceFilename(targetSequenceFilename),
          sliceMatchSize(sliceMatchSize), querySequenceFileIndex(querySequenceFileIndex),
          targetSequenceFileIndex(targetSequenceFileIndex),
          outputFilename(generateOutputFilename(querySequenceFilename, targetSequenceFilename, sliceMatchSize)) {}

ApproximateAligner::ApproximateAligner(
        const std::string &querySequenceFilename, const std::string &targetSequenceFilename, int sliceMatchSize)
        : ApproximateAligner(querySequenceFilename, targetSequenceFilename, filenameWillAutogenerate,
                             sliceMatchSize) {}

ApproximateAligner::~ApproximateAligner() = default;

void ApproximateAligner::align() {
    auto *queryFastaFile = new FastaFileContent(this->querySequenceFilename),
            *targetFastaFile = new FastaFileContent(this->targetSequenceFilename);

    auto sliceMatcher = new GlobalApproximateSliceMatcher(
            queryFastaFile->sequences.at(this->querySequenceFileIndex),
            targetFastaFile->sequences.at(this->targetSequenceFileIndex),
            this->sliceMatchSize);

    auto fileFormatter = new ApproximateSliceMatchesFileFormat(this->outputFilename);
    fileFormatter->write(sliceMatcher);

    delete sliceMatcher;
    delete fileFormatter;
    delete queryFastaFile;
    delete targetFastaFile;
}

std::string replaceAll(std::string, const std::string &, const std::string &);

std::string generateOutputFilename(const std::string &queryFilepath, const std::string &targetFilepath, int sliceSize) {
    return replaceAll(replaceAll(queryFilepath, "/", "_"), ".fasta", "") + "_" +
           replaceAll(replaceAll(targetFilepath, "/", "_"), ".fasta", "") + "_" +
           std::to_string(sliceSize) + ".txt";
}

std::string replaceAll(std::string str, const std::string &from, const std::string &to) {
    if (from.empty())
        return str;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
    return str;
}

