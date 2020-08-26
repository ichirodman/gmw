#include <string>
#include <iostream>
#include "utils/fasta.hpp"
#include <vector>
#include <array>
#include <cmath>

#define SLICE_LEN 1000
#define VOCABULARY_SIZE 4
#define TRIPLET_LEN 3
#define msegs vector<pair<pair<int, int>, pair<int, int>>>

using namespace std;

bool is_indexes_in_any_pair_of_matched_segments(msegs *matched_segments, int query_index, int target_index);

template <typename T>
int get_additive_end_of_match_segment(T *query_occurrence_array, T *target_occurrence_array, int start_index);

auto *init_occurrence_array();

template <typename T>
void delete_occurrence_array(T *);

template <typename T>
short int get_next_query_triplet_code(int, T *);

bool is_triplet_in_current_code_triplets(int, vector<int> *);

int get_index(vector<int> *, int);

short int get_nucleotide_code(char);

short int encode_triplet(string &);

auto *get_occurrence_array(const FastaSequence *);

msegs *get_matched_segments(const FastaSequence *, const FastaSequence *);

int main()
{
    string query_file("small/source.fasta"), target_file("small/deletion.fasta");
    FastaFileContent *query = new FastaFileContent(query_file);
    FastaFileContent *target = new FastaFileContent(target_file);

    msegs *matched_segments = get_matched_segments(query->sequences[0], target->sequences[0]);

    cout << "Matched segments amount : " << matched_segments->size() << endl;

    return 0;
}

auto *init_occurrence_array()
{
    const size_t occurrence_array_size = pow(VOCABULARY_SIZE, TRIPLET_LEN);
    auto *occurrence_array = new array<vector<int> *, occurrence_array_size>();
    for (int i = 0; i < occurrence_array->size(); ++i)
    {
        occurrence_array->at(i) = new vector<int>();
    }
    return occurrence_array;
}

template <typename T>
void delete_occurrence_array(T *occurrence_array)
{
    for (size_t i = 0; i < occurrence_array->size(); ++i)
    {
        occurrence_array->at(i)->clear();
        delete occurrence_array->at(i);
    }
    delete[] occurrence_array;
}

template <typename T>
int get_triplet_code(int triplet_index, T *occurrence_array)
{
    for (int triplet_code = 0; triplet_code < occurrence_array->size(); ++triplet_code)
    {
        if (is_triplet_in_current_code_triplets(triplet_index, occurrence_array->at(triplet_code)))
        {
            return triplet_code;
        }
    }
    return -1;
}

bool is_triplet_in_current_code_triplets(int triplet_code, vector<int> *current_code_triplets)
{
    return get_index(current_code_triplets, triplet_code) != -1;
}

int get_index(vector<int> *arr, int val)
{
    for (int left = 0, right = arr->size() - 1, mid = (left + right) / 2;
         left <= right; mid = (left + right) / 2)
    {
        if (val < arr->at(mid))
            right = mid - 1;
        else if (val > arr->at(mid))
            left = mid + 1;
        else
            return mid;
    }
    return -1;
}

bool is_indexes_in_any_pair_of_matched_segments(msegs *matched_segments, int query_index, int target_index)
{
    for (int pair_i = 0; pair_i < matched_segments->size(); ++pair_i)
    {
        if (matched_segments->at(pair_i).first.first <= query_index &&
            matched_segments->at(pair_i).first.second >= query_index &&
            matched_segments->at(pair_i).second.first <= target_index &&
            matched_segments->at(pair_i).second.second >= target_index)
        {
            return true;
        }
    }
    return false;
}

template <typename T>
int get_additive_end_of_match_segment(T *query_occurrence_array, T *target_occurrence_array,
                                      int query_start_index, int target_start_index)
{
    int additive_i = 0;
    for (int query_triplet_code, target_triplet_code;; ++additive_i)
    {
        query_triplet_code = get_triplet_code(query_start_index + additive_i, query_occurrence_array);
        target_triplet_code = get_triplet_code(target_start_index + additive_i, target_occurrence_array);

        // cout << "i : " << query_start_index + additive_i << " " << target_start_index + additive_i << " " << query_triplet_code << " " << target_triplet_code << endl;

        if (query_triplet_code != target_triplet_code || query_triplet_code == -1 || target_triplet_code == -1)
        {
            return additive_i;
        }
    }
}

short int get_nucleotide_code(char nucleotide)
{
    switch (nucleotide)
    {
    case 'a':
    case 'A':
        return 0;
    case 'c':
    case 'C':
        return 1;
    case 'g':
    case 'G':
        return 2;
    case 't':
    case 'T':
        return 3;
    default:
        cerr << "ERROR: "
             << "Strange nucleotide : " << nucleotide << endl;
        return -1;
    }
}

short int encode_triplet(string &triplet)
{
    short int code = 0;
    for (size_t i = 0; i < TRIPLET_LEN; ++i)
    {
        short int rank = pow(VOCABULARY_SIZE, TRIPLET_LEN - i - 1);
        short int nucleotide_code = get_nucleotide_code(triplet[i]);
        code += rank * nucleotide_code;
    }
    return code;
}

auto *get_occurrence_array(const FastaSequence *sequence)
{
    auto *occurrence_array = init_occurrence_array();
    for (int i = 0, sequence_len = sequence->source->size(); i < sequence_len - TRIPLET_LEN + 1; ++i)
    {
        string subseq = sequence->source->substr(i, TRIPLET_LEN);
        short int triplet_code = encode_triplet(subseq);
        occurrence_array->at(triplet_code)->push_back(i);
    }
    return occurrence_array;
}

msegs *get_matched_segments(const FastaSequence *query, const FastaSequence *target)
{
    auto *query_triplet_occurrence = get_occurrence_array(query);
    cout << "Query triplet occurrence array got" << endl;
    auto *target_triplet_occurrence = get_occurrence_array(target);
    cout << "Target triplet occurrence array got" << endl;

    msegs *matched_segments = new msegs();

    for (short int triplets_code = 0;
         triplets_code < query_triplet_occurrence->size() && triplets_code < target_triplet_occurrence->size();
         ++triplets_code)
    {
        cout << "Now checking code : " << triplets_code << endl;
        for (int query_i = 0; query_i < query_triplet_occurrence->at(triplets_code)->size(); ++query_i)
        {
            for (int target_i = 0; target_i < target_triplet_occurrence->at(triplets_code)->size(); ++target_i)
            {
                int query_triplet_index = query_triplet_occurrence->at(triplets_code)->at(query_i),
                    target_triplet_index = target_triplet_occurrence->at(triplets_code)->at(target_i);
                if (!is_indexes_in_any_pair_of_matched_segments(matched_segments, query_triplet_index, target_triplet_index))
                {
                    int additive_i = get_additive_end_of_match_segment(query_triplet_occurrence, target_triplet_occurrence, query_triplet_index, target_triplet_index);

                    if (additive_i > 10)
                    {
                        cout << query_triplet_index << "->" << query_triplet_index + additive_i << " : " << target_triplet_index << "->" << target_triplet_index + additive_i << endl;
                        auto query_segment = pair<int, int>(query_triplet_index, query_triplet_index + additive_i);
                        auto target_segment = pair<int, int>(target_triplet_index, target_triplet_index + additive_i);
                        auto segments_pair = pair<pair<int, int>, pair<int, int>>(query_segment, target_segment);
                        matched_segments->push_back(segments_pair);
                    }
                }
                else
                {
                    // cout << "ALREADY EXIST" << endl;
                }
            }
        }
    }

    int end = get_additive_end_of_match_segment(query_triplet_occurrence, target_triplet_occurrence, 0, 0);
    cout << "Lengths:  query : " << query->source->length() << "  target : " << target->source->length() << endl;
    cout << "MATCHED : " << end << endl;

    delete_occurrence_array(query_triplet_occurrence);
    delete_occurrence_array(target_triplet_occurrence);

    return matched_segments;
}
