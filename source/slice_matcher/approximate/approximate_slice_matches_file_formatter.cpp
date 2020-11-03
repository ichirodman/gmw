//
// Created by ichigo on 02.11.2020.
//

#include "approximate_slice_matches_file_formatter.hpp"

#include <iostream>
#include <functional>
#include <fstream>


ApproximateSliceMatchesFileFormat::ApproximateSliceMatchesFileFormat(const std::string &filename)
        : filename(filename) {}

ApproximateSliceMatchesFileFormat::~ApproximateSliceMatchesFileFormat() {}

void writeToOutputFile(const std::string &, const std::string &);

const std::string generateFileContent(GlobalApproximateSliceMatcher *);

void ApproximateSliceMatchesFileFormat::write(GlobalApproximateSliceMatcher *sliceMatcher) {
    const std::string fileContent = generateFileContent(sliceMatcher);
    writeToOutputFile(this->filename, fileContent);
}

GlobalApproximateSliceMatcher *ApproximateSliceMatchesFileFormat::extract() {
    return nullptr; // TODO
}

const std::string generateFileContent(GlobalApproximateSliceMatcher *sliceMatcher) {
    return "> Q : " + sliceMatcher->getQuerySequenceDescription() + "\n" +
           "> T : " + sliceMatcher->getTargetSequenceDescription() + "\n" +
           sliceMatcher->getSliceEntriesStringRepr();
}

const std::string getPath(const std::string &);

void writeToOutputFile(const std::string &filename, const std::string &content) {
    std::string filePath = getPath(filename);
    std::ofstream outputFile(filePath);
    outputFile << content << std::endl;
    outputFile.close();
}

const std::string getPath(const std::string &filename) { return FILES_OUTPUT_DIR + filename; }
