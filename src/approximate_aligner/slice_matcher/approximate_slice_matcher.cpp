//
// Created by ichigo on 02.11.2020.
//


#include "approximate_slice_matcher.hpp"

#include <functional>
#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>


GlobalApproximateSliceMatcher::GlobalApproximateSliceMatcher(FastaSequence *querySeq, FastaSequence *targetSeq,
                                                             int thresholdMatchLength)
        : querySequenceSuffixForest(new SuffixForest(querySeq)), targetSequence(targetSeq),
          thresholdMathLength(thresholdMatchLength),
          slicesEntries(new ComparativeEntries()) {
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

const std::string getReversed(const std::string);

const std::string getComplimentary(const std::string &);

const std::string getLexicographicallyMinSubsequenceVariant(const std::string &);

std::vector<int> *getSliceEntries(SuffixForest *, const std::string &);

SliceEntries GlobalApproximateSliceMatcher::getQueryAndTargetSubstringEntries(const std::string &keySubsequence) {
    return slicesEntries->at(getLexicographicallyMinSubsequenceVariant(keySubsequence));
}

bool hasKey(ComparativeEntries *, const std::string &);

void increaseKeySlice(ComparativeEntries *, std::string, std::string);

template<class T>
bool hasElement(std::vector<T> *, const T &);

template<class T>
void deleteElement(std::vector<T> &, const T &);

template<class T>
auto getElementPointer(std::vector<T> &, const T &);

void GlobalApproximateSliceMatcher::findSlicesEntries() {
    std::cout << "-- Finding sequences slices entries --" << std::endl;

    std::string sliceTryingToComplete;

    auto addSlice = [this](std::vector<int> *queryEntries, const std::string &keySlice, int targetEntryIndex) {
        if (hasKey(this->slicesEntries, keySlice)) {
            if (!hasElement(slicesEntries->at(keySlice).first, targetEntryIndex)) {
                slicesEntries->at(keySlice).first->push_back(targetEntryIndex);
            }
        } else {
            slicesEntries->insert({keySlice, std::pair<std::vector<int> *, std::vector<int> *>(
                    {new std::vector<int>({targetEntryIndex}), queryEntries})});
        }
    };

    auto handleSlice = [this, &sliceTryingToComplete, &addSlice]
            (std::vector<int> *queryEntries, const std::string &keySlice, int targetEntryIndex) {
//        std::cout << "starting : " << sliceTryingToComplete << " : "
//                  << hasKey(this->slicesEntries, sliceTryingToComplete) << std::endl;
        if (queryEntries->size() == 0) {
//            std::cout << "D-1.1" << std::endl;
            sliceTryingToComplete.clear();
//            std::cout << "D-1.2" << std::endl;
            return;
        } else if (sliceTryingToComplete.size() == 0) {
//            std::cout << "D0.1" << std::endl;
            addSlice(queryEntries, keySlice, targetEntryIndex);
//            std::cout << "D0.2" << std::endl;
        } else if (queryEntries->size() != 1) {
//            std::cout << "D1.1" << std::endl;
            sliceTryingToComplete.clear();
//            std::cout << "D1.2" << std::endl;
            addSlice(queryEntries, keySlice, targetEntryIndex);
//            std::cout << "D1.3" << std::endl;
        } else if (std::abs(this->slicesEntries->at(sliceTryingToComplete).first->at(0)) +
                   sliceTryingToComplete.length() == abs(targetEntryIndex)) {
//            std::cout << "D2.1" << std::endl;
            increaseKeySlice(this->slicesEntries, sliceTryingToComplete, sliceTryingToComplete + keySlice);
//            std::cout << "D2.2";//<< std::endl;
        } else {
//            std::cout << "D3.1" << std::endl;
            sliceTryingToComplete.clear();
//            std::cout << "D3.2" << std::endl;
            addSlice(queryEntries, keySlice, targetEntryIndex);
//            std::cout << "D3.3" << std::endl;
        }
        sliceTryingToComplete += keySlice;
//        std::cout << "finishing : " << sliceTryingToComplete << std::endl;
    };

    for (int i = 0, percentage = 0, max_i = targetSequence->source->length() / thresholdMathLength; i < max_i; i++) {
        if (percentage - 1 < (100 * i) / max_i) {
            percentage++;
            std::cout << percentage << " ... " << std::flush;
        }

        int sliceTargetEntryIndex = i * thresholdMathLength;
        const std::string keySlice = getLexicographicallyMinSubsequenceVariant(
                targetSequence->source->substr(sliceTargetEntryIndex, thresholdMathLength));

        auto queryEntries = getSliceEntries(querySequenceSuffixForest, keySlice);
        handleSlice(queryEntries, keySlice, sliceTargetEntryIndex);
    }
    std::cout << std::endl << "Finished" << std::endl;
}

const std::string &GlobalApproximateSliceMatcher::getQuerySequenceDescription() {
    return this->querySequenceSuffixForest->getSequenceDescription();
}

const std::string &GlobalApproximateSliceMatcher::getTargetSequenceDescription() {
    return *(this->targetSequence->description);
}

std::vector<int> *getSliceEntries(SuffixForest *suffixForest, const std::string &slice) {
    auto sliceEntries = new std::vector<int>();
    std::vector<std::pair<std::string, int>> sliceVariationsAndDirections = {
            {slice,                                1},
            {getComplimentary(slice),              1},
            {getReversed(slice),                   -1},
            {getComplimentary(getReversed(slice)), -1}};
    for (auto &variantAndDirection: sliceVariationsAndDirections) {
        auto variantEntries = suffixForest->getEntryIndexes(variantAndDirection.first);
        for (auto entry: *variantEntries) {
            sliceEntries->push_back(entry * variantAndDirection.second);
        }
        delete variantEntries;
    }
    return sliceEntries;
}

bool hasKey(ComparativeEntries *m, const std::string &k) {
    return m->find(k) != m->end();
}

void increaseKeySlice(ComparativeEntries *m, std::string oldKey, std::string newKey) {
    auto entry = m->find(oldKey);
    auto const value = std::move(entry->second);
    m->erase(entry);
    m->insert({newKey, std::move(value)});
    if (m->at(newKey).first->at(0) < 0) {
        m->at(newKey).first->at(0) -= (newKey.length() - oldKey.length());
    }
    if (m->at(newKey).second->at(0) < 0) {
        m->at(newKey).second->at(0) -= (newKey.length() - oldKey.length());
    }
}

template<class T>
bool hasElement(std::vector<T> *v, const T &e) {
    return v->size() > 0 && std::find(v->begin(), v->end(), e) != v->end();
}


template<class T>
void deleteElement(std::vector<T> &v, const T &e) {
    v.erase(std::find(v.begin(), v.end(), e));
}

template<class T>
auto getElementPointer(std::vector<T> &v, const T &e) {
    return std::find(v.begin(), v.end(), e);
}

char getComplimentaryNucleotide(char);

const std::string getReversed(std::string string) {
    std::reverse(string.begin(), string.end());
    return string;
}

const std::string getComplimentary(const std::string &string) {
    std::string complimentary = "";
    for (int i = 0; i < string.length(); ++i) {
        complimentary += getComplimentaryNucleotide(string.at(i));
    }
    return complimentary;
}

const std::string getLexicographicallyMinSubsequenceVariant(const std::string &subsequence) {
    std::vector<std::string> allVariants = {subsequence, getReversed(subsequence), getComplimentary(subsequence),
                                            getReversed(getComplimentary(subsequence))};
    std::sort(allVariants.begin(), allVariants.end());
    return allVariants.at(0);
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

