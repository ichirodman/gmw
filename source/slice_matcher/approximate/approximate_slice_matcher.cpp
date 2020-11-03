//
// Created by ichigo on 02.11.2020.
//


#include "approximate_slice_matcher.hpp"


GlobalApproximateSliceMatcher::GlobalApproximateSliceMatcher(FastaSequence *querySeq, FastaSequence *targetSeq)
        : querySequenceSuffixForest(new SuffixForest(querySeq)), targetSequence(targetSeq),
          slicesEntries(new std::map<const std::string, std::pair<std::vector<int> *, std::vector<int> *>>()) {
    this->querySequenceSuffixForest->build();
    this->writeSlicesEntries();
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

bool haveKey(std::map<const std::string, std::pair<std::vector<int> *, std::vector<int> *>> *, const std::string &);

void GlobalApproximateSliceMatcher::writeSlicesEntries() {
    for (int i = 0; i < targetSequence->source->length() / THRESHOLD_MATCH_LENGTH; i++) {
        const std::string targetSequenceSlice = targetSequence->source->substr(i * THRESHOLD_MATCH_LENGTH,
                                                                               THRESHOLD_MATCH_LENGTH);
        if (haveKey(slicesEntries, targetSequenceSlice)) {
            slicesEntries->at(targetSequenceSlice).first->push_back(i);
        } else {
            auto queryTargetSliceEntries = querySequenceSuffixForest->getEntryIndexes(targetSequenceSlice);
            slicesEntries->insert({targetSequenceSlice, std::pair<std::vector<int> *, std::vector<int> *>(
                    {new std::vector<int>({i * THRESHOLD_MATCH_LENGTH}), queryTargetSliceEntries})});
        }
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

bool haveKey(std::map<const std::string, std::pair<std::vector<int> *, std::vector<int> *>> *m, const std::string &k) {
    return m->find(k) != m->end();
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
