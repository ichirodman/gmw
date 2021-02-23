//
// Created by ichigo on 02.11.2020.
//

#include "approximate_slice_matches_file_formatter.hpp"

#include <iostream>
#include <functional>
#include <fstream>


ApproximateSliceMatchesFileFormat::ApproximateSliceMatchesFileFormat(const std::string &filename)
        : filename(filename) {}

ApproximateSliceMatchesFileFormat::~ApproximateSliceMatchesFileFormat() = default;

void writeToOutputFile(const std::string &, const std::string &, ComparativeEntries *);

const std::string generateFileHeaders(GlobalApproximateSliceMatcher *);

void ApproximateSliceMatchesFileFormat::write(GlobalApproximateSliceMatcher *sliceMatcher) {
    std::cout << "-- Writing slice matches to file : " << this->filename << " --" << std::endl;
    const std::string fileHeaders = generateFileHeaders(sliceMatcher);
    writeToOutputFile(this->filename, fileHeaders, sliceMatcher->slicesEntries);
}

GlobalApproximateSliceMatcher *ApproximateSliceMatchesFileFormat::extract() {
    return nullptr; // TODO
}

const std::string generateFileHeaders(GlobalApproximateSliceMatcher *sliceMatcher) {
    return "> Q : " + sliceMatcher->getQuerySequenceDescription() + "\n" +
           "> T : " + sliceMatcher->getTargetSequenceDescription() + "\n";
}

const std::string getPath(const std::string &);

const std::string getCurrentSliceStringRepr(const std::string slice, std::pair<std::vector<int> *,
        std::vector<int> *> &currentSliceEntries);

void writeToOutputFile(const std::string &filename, const std::string &headers, ComparativeEntries *slicesEntries) {
    std::string filePath = getPath(filename);
    std::ofstream outputFile(filePath);
    outputFile << headers;
    std::cout << headers << " , " << outputFile.is_open() << std::endl;
    for (auto it = slicesEntries->begin(); it != slicesEntries->end(); it++) {
//        std::cout << "S : " << std::flush;
//        std::cout << it->first << " ";
//        for (auto &e: *it->second.first)
//            std::cout << e << " ";
//        std::cout << " : ";
//        for (auto &e: *it->second.second)
//            std::cout << e << " ";
//        std::cout << std::endl;
//            std::cout << getCurrentSliceStringRepr(it->first, it->second) << std::endl;
        outputFile << getCurrentSliceStringRepr(it->first, it->second) << "\n";
    }
    outputFile.close();
}

const std::string join(const std::string, std::vector<int> *);

const std::string getCurrentSliceStringRepr(const std::string slice, std::pair<std::vector<int> *,
        std::vector<int> *> &currentSliceEntries) {
    return slice + " : " +
           join(",", currentSliceEntries.first) + " ; " +
           join(",", currentSliceEntries.second);
}

const std::string getPath(const std::string &filename) {
    return FILES_OUTPUT_DIR + filename;
}

const std::string join(const std::string joinTo, std::vector<int> *v) {
    std::string repr = "";
    for (int i = 0; i < v->size(); ++i) {
        repr += std::to_string(v->at(i));
        if (i < v->size() - 1) {
            repr += joinTo;
        }
    }
    return repr;
}