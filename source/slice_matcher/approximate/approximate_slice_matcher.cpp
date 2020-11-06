//
// Created by ichigo on 02.11.2020.
//


#include "approximate_slice_matcher.hpp"

#include <functional>
#include <iostream>
#include <algorithm>


GlobalApproximateSliceMatcher::GlobalApproximateSliceMatcher(FastaSequence *querySeq, FastaSequence *targetSeq,
                                                             int thresholdMatchLength)
        : querySequenceSuffixForest(new SuffixForest(querySeq)), targetSequence(targetSeq),
          thresholdMathLength(thresholdMatchLength),
          slicesEntries(new std::map<const std::string, std::pair<std::vector<int> *, std::vector<int> *>>()) {
    this->querySequenceSuffixForest->build();
    this->findSlicesEntries();
}

GlobalApproximateSliceMatcher::~GlobalApproximateSliceMatcher() {
    delete querySequenceSuffixForest;
    delete targetSequence;
    for (auto it = slicesEntries->begin(); it != slicesEntries->end(); ++it) {
        delete it->second.first;
        delete it->second.second;
    }
    delete slicesEntries;
}

std::pair<std::vector<int> *, std::vector<int> *>
GlobalApproximateSliceMatcher::getQueryAndTargetSubstringEntries(const std::string &keySubsequence) {
    return this->slicesEntries->at(keySubsequence);
}

bool haveKey(std::map<const std::string, std::pair<std::vector<int> *, std::vector<int> *>> *,
             const std::string &);

const std::string getComplimentary(const std::string &);

void GlobalApproximateSliceMatcher::findSlicesEntries() {
    std::cout << "-- Finding sequences slices entries --" << std::endl;

    std::function<void(const std::string &, int)>
            handleNewSuffix = [this](const std::string &targetSequenceSlice, int entryIndex) {
        if (haveKey(slicesEntries, targetSequenceSlice)) {
            slicesEntries->at(targetSequenceSlice).first->push_back(entryIndex);
        } else {
            auto queryTargetSliceEntries = querySequenceSuffixForest->getEntryIndexes(targetSequenceSlice);
            slicesEntries->insert(
                    {targetSequenceSlice, std::pair<std::vector<int> *, std::vector<int> *>(
                            {new std::vector<int>({entryIndex}), queryTargetSliceEntries})});
        }
    };

    for (int i = 0; i < targetSequence->source->length() / thresholdMathLength; i++) {
        int sliceQueryEntryIndex = i * thresholdMathLength;
        std::string targetSequenceSlice = targetSequence->source->substr(sliceQueryEntryIndex, thresholdMathLength),
                reversedTargetSequenceSlice = targetSequenceSlice;
        std::reverse(reversedTargetSequenceSlice.begin(), reversedTargetSequenceSlice.end());
        std::string targetSequenceComplimentarySlice = getComplimentary(targetSequenceSlice),
                reversedTargetSequenceComplimentarySlice = getComplimentary(reversedTargetSequenceSlice);

        handleNewSuffix(targetSequenceSlice, sliceQueryEntryIndex);
        handleNewSuffix(targetSequenceComplimentarySlice, sliceQueryEntryIndex);
        handleNewSuffix(reversedTargetSequenceSlice, -sliceQueryEntryIndex);
        handleNewSuffix(reversedTargetSequenceComplimentarySlice, -sliceQueryEntryIndex);
    }
}

const std::string &GlobalApproximateSliceMatcher::getQuerySequenceDescription() {
    return this->querySequenceSuffixForest->getSequenceDescription();
}

const std::string &GlobalApproximateSliceMatcher::getTargetSequenceDescription() {
    return *(this->targetSequence->description);
}

const std::string getCurrentSliceStringRepr(const std::string slice,
                                            std::pair<std::vector<int> *, std::vector<int> *> currentSliceEntries);

const std::string GlobalApproximateSliceMatcher::getSliceEntriesStringRepr() {
    std::string repr = "";
    for (auto it = this->slicesEntries->begin(); it != slicesEntries->end(); it++) {
        if (it->second.second->size() != 0) {
            repr += getCurrentSliceStringRepr(it->first, it->second) + "\n";
        }
    }
    return repr;
}

bool haveKey(std::map<const std::string, std::pair<std::vector<int> *, std::vector<int> *>> *m,
             const std::string &k) {
    return m->find(k) != m->end();
}

char getComplimentaryNucleotide(char);

const std::string getComplimentary(const std::string &string) {
    std::string complimentary = "";
    for (int i = 0; i < string.length(); ++i) {
        complimentary += getComplimentaryNucleotide(string.at(i));
    }
    return complimentary;
}

char getComplimentaryNucleotide(char nucleotide) {
    switch (nucleotide) {
        case 'a':
        case 'A':
            return 'T';
        case 'c':
        case 'C':
            return 'G';
        case 'g':
        case 'G':
            return 'C';
        case 't':
        case 'T':
            return 'A';
        default:
            return 'N';
    }
}

const std::string join(const std::string, std::vector<int> *);

const std::string getCurrentSliceStringRepr(const std::string slice,
                                            std::pair<std::vector<int> *, std::vector<int> *> currentSliceEntries) {
    return slice + " : " +
           join(",", currentSliceEntries.first) + " ; " +
           join(",", currentSliceEntries.second);
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
