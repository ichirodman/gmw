//
// Created by ichigo on 18.10.2020.
//

#ifndef GMW_GLOBAL_APPROXIMATE_SLICE_MATCHER_HPP
#define GMW_GLOBAL_APPROXIMATE_SLICE_MATCHER_HPP

#include <map>

#include "../../suffix_forest/suffix_forest.hpp"
#include "../../utils/fasta.hpp"

#define THRESHOLD_MATCH_LENGTH 200


class GlobalApproximateSliceMatcher {
public:
    GlobalApproximateSliceMatcher(FastaSequence *, FastaSequence *);

    ~GlobalApproximateSliceMatcher();

    std::pair<std::vector<int> *, std::vector<int> *> getQueryAndTargetSubstringEntries(const std::string &);

    const std::string &getQuerySequenceDescription();

    const std::string &getTargetSequenceDescription();

    const std::string getSliceEntriesStringRepr();

private:
    void writeSlicesEntries();

    SuffixForest *querySequenceSuffixForest;

    FastaSequence *targetSequence;

    std::map<const std::string, std::pair<std::vector<int> *, std::vector<int> *>> * slicesEntries;
};

#endif //GMW_GLOBAL_APPROXIMATE_SLICE_MATCHER_HPP
