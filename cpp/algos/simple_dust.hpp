#pragma once
#include <string>
#include "../utils/fasta.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>

using namespace std;

// DEBUG FUNCTION
// ONLY FOR ARRAYS WITH SIZE 64
void print_arr(int *arr)
{
    for (int i = 0; i < 4 * 4 * 4; i++)
        cout << arr[i] << " ";
    cout << endl;
};

int get_nucleotide_index(char nucliotide)
{
    switch (nucliotide)
    {
    case 'A':
        return 0;
    case 'C':
        return 1;
    case 'G':
        return 2;
    case 'T':
        return 3;
    default:
        cerr << "Strange nucleotide : " << nucliotide << endl;
        return -1;
    }
};

int get_slice_index(string slice)
{
    int code = 0;
    const int slice_length = slice.length();
    for (int i = 0; i < slice_length; i++)
        code += get_nucleotide_index(slice[i]) * pow(4, slice_length - i - 1);
    return code;
};

float count_subseq_score(int *occurrence_array, int array_length, int *additive_array = nullptr)
{
    if (additive_array == nullptr)
    {
        float sum_score = 0.0;
        int slices_amount = 0;
        for (int i = 0; i < array_length; i++)
        {
            if (occurrence_array[i] != 0)
            {
                slices_amount += occurrence_array[i];
                sum_score += occurrence_array[i] * (occurrence_array[i] + 1) / 2.0;
            }
        }
        return static_cast<float>(sum_score) / (static_cast<float>(slices_amount) - 1.0);
    }
    else
    {
        int sum_score = 0, slices_amount;
        for (int i = 0; i < array_length; i++)
        {
            slices_amount += occurrence_array[i];
            sum_score += (occurrence_array[i] + additive_array[i]) * (occurrence_array[i] + 1 + additive_array[i]) / 2.0;
        }
        return sum_score / (slices_amount - 1.0);
    }
}

void dust(FastaSequence const *seq, int min_len = 7, float score_increase_threshold = 2.25,
          float threshold_score_difference = 0.7, bool print_progress = false, bool debug = false)
{
    const int slice_len = 3, slices_amount = min_len - 2, slice_indexes_amount = static_cast<int>(pow(4, slice_len));

    int amount_array[slice_indexes_amount];
    memset(amount_array, 0, sizeof(int) * slice_indexes_amount);

    vector<pair<int, int>> *filtered_out = new vector<pair<int, int>>();

    for (int i = 0, seq_len = seq->source.length(), done = 0; i + slice_len < seq_len; i++)
    {
        if (print_progress && (int)(round((i + 1) * 100.0 / (seq_len - slice_len))) > done)
        {
            done = (int)(round((i + 1) * 100.0 / (seq_len - slice_len)));
            cout << "Dust done : " << done << "%" << endl;
        }

        const string new_slice = seq->source.substr(i, slice_len);
        const int new_slice_index = get_slice_index(new_slice);
        amount_array[new_slice_index]++;

        int slices_now_in_amount = 0;
        for (int j = 0; j < slice_indexes_amount; j++)
        {
            slices_now_in_amount += amount_array[j];
        }

        if (debug)
        {
            print_arr(amount_array);
        }

        if (slices_now_in_amount > slices_amount)
        {
            const string old_slice = seq->source.substr(i - slices_amount, slice_len);
            const int old_slice_index = get_slice_index(old_slice);
            amount_array[old_slice_index]--;

            const float subseq_score = count_subseq_score(amount_array, slice_indexes_amount);
            if (subseq_score > score_increase_threshold + 1e-2)
            {
                int good_additive_i = 0;
                int additive_amount_array[slice_indexes_amount];
                ::memset(additive_amount_array, 0, sizeof(int) * slice_indexes_amount);

                int score_to_compare_with = subseq_score;
                vector<int> *new_score = new vector<int>();
                for (int additive_i = 1;; additive_i++)
                {
                    const string slice_out_of_bounds = seq->source.substr(i + additive_i, slice_len);
                    const int slice_out_of_bounds_index = get_slice_index(slice_out_of_bounds);
                    additive_amount_array[slice_out_of_bounds_index]++;
                    new_score->push_back(count_subseq_score(amount_array, slice_indexes_amount, additive_amount_array));
                    if (new_score->size() > 3)
                    {
                        if (new_score->back() - score_to_compare_with < threshold_score_difference)
                        {
                            if (debug)
                            {
                                print_arr(amount_array);
                                print_arr(additive_amount_array);
                                cout << "Score for it : " << subseq_score << endl
                                     << endl;
                            }
                            if (new_score->size() > 3)
                            {
                                break;
                            }
                        }
                        else
                        {
                            good_additive_i = additive_i;
                        }
                        score_to_compare_with = new_score->back();
                    }
                }

                delete new_score;
                
                pair<int, int> low_complexity_region(i - slices_amount + 1 + 1, i + slice_len + good_additive_i - 1);
                filtered_out->push_back(low_complexity_region);

                i = filtered_out->back().second;
                ::memset(amount_array, 0, sizeof(int) * slice_indexes_amount);
            }
        }
    }

    for (pair<int, int> p : *filtered_out)
    {
        for (int i = p.first; i < p.second; i++)
        {
            seq->source[i] = tolower(seq->source[i]);
        }
        if (debug)
        {
            cout << p.first << "->" << p.second << " : " << seq->source.substr(p.first - 5, 5) << "|"
                 << seq->source.substr(p.first, p.second - p.first) << "|" << seq->source.substr(p.second + 5, 5) << endl;
        }
    }

    delete filtered_out;
};
