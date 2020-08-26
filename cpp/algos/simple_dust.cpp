#include "simple_dust.hpp"
#include <functional>

using namespace std;

// DEBUG FUNCTION
void print_arr(int *arr, int len)
{
    for (int i = 0; i < len; i++)
        cout << arr[i] << " ";
    cout << endl;
};

int sum_elements(int *arr, int len)
{
    int sum = 0;
    for (int i = 0; i < len; i++)
        sum += arr[i];
    return sum;
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
    const int slice_length = slice.length();
    int code = 0;
    for (int i = 0; i < slice_length; i++)
    {
        code += get_nucleotide_index(slice[i]) * pow(4, slice_length - i - 1);
    }
    return code;
};

void dust(FastaSequence const *seq, int min_len, float score_increase_threshold,
          float threshold_score_difference, bool print_progress, bool debug)
{
    function<float(int *, int, int *)> count_subseq_score = [](int *occurrence_array, int array_length, int *additive_array = nullptr) {
        float sum_score = 0.0;
        int slices_amount = 0;
        for (int i = 0; i < array_length; i++)
        {
            int occurrence_i_value = occurrence_array[i] + (additive_array == nullptr ? 0 : additive_array[i]);
            slices_amount += occurrence_i_value;
            sum_score += static_cast<float>(occurrence_i_value * (occurrence_i_value + 1)) / 2.0;
        }
        return static_cast<float>(sum_score) / (static_cast<float>(slices_amount) - 1.0);
    };

    function<void(int *, int, int)> increment_slice_occurrence = [seq](int *occurrence_array, int index, int slice_len) {
        const string new_slice = seq->source->substr(index, slice_len);
        const int new_slice_index = get_slice_index(new_slice);
        occurrence_array[new_slice_index]++;
    };

    function<void(int *, int, int)> decrement_slice_occurrence = [seq](int *occurrence_array, int index, int slice_len) {
        const string new_slice = seq->source->substr(index, slice_len);
        const int new_slice_index = get_slice_index(new_slice);
        occurrence_array[new_slice_index]--;
    };

    const int slice_len = 3, slices_amount = min_len - 2, slice_indexes_amount = static_cast<int>(pow(4, slice_len));

    int amount_array[slice_indexes_amount];
    ::memset(amount_array, 0, sizeof(int) * slice_indexes_amount);

    vector<pair<int, int>> *filtered_out = new vector<pair<int, int>>();

    for (int i = 0, seq_len = seq->source->length(), done = 0; i + slice_len < seq_len; i++)
    {
        if (print_progress && static_cast<int>(round((i + 1) * 100.0 / (seq_len - slice_len))) > done)
        {
            done = static_cast<int>(round((i + 1) * 100.0 / (seq_len - slice_len)));
            cout << "Dust done : " << done << "%" << endl;
        }

        increment_slice_occurrence(amount_array, i, slice_len);

        int slices_now_in_amount = sum_elements(amount_array, slice_indexes_amount);

        if (debug)
        {
            print_arr(amount_array, slice_indexes_amount);
        }

        if (slices_now_in_amount > slices_amount)
        {
            decrement_slice_occurrence(amount_array, i - slices_amount, slice_len);

            const float subseq_score = count_subseq_score(amount_array, slice_indexes_amount, nullptr);
            if (subseq_score > score_increase_threshold + 1e-2)
            {
                int good_additive_i = 0;
                int additive_amount_array[slice_indexes_amount];
                ::memset(additive_amount_array, 0, sizeof(int) * slice_indexes_amount);

                int score_to_compare_with = subseq_score;
                vector<int> *new_score = new vector<int>();
                for (int additive_i = 1;; additive_i++)
                {
                    increment_slice_occurrence(additive_amount_array, i + additive_i - 1, slice_len);

                    int additive_subseq_score = count_subseq_score(amount_array, slice_indexes_amount, additive_amount_array);
                    new_score->push_back(additive_subseq_score);

                    if (new_score->back() - score_to_compare_with < threshold_score_difference)
                    {
                        if (debug)
                        {
                            print_arr(amount_array, slice_indexes_amount);
                            print_arr(additive_amount_array, slice_indexes_amount);
                            cout << "Score for it : " << subseq_score << endl
                                 << endl;
                        }
                        if (new_score->size() > 4)
                        {
                            break;
                        }
                    }
                    else
                    {
                        score_to_compare_with = new_score->back();
                        good_additive_i = additive_i;
                    }
                }

                delete new_score;

                pair<int, int> low_complexity_region(i - slices_amount + 1 + 1, i + slice_len + good_additive_i - 1);
                filtered_out->push_back(low_complexity_region);

                if (true)
                {
                    cout << low_complexity_region.first << "->" << low_complexity_region.second << " : " << seq->source->substr(low_complexity_region.first - 5, 5) << "|"
                         << seq->source->substr(low_complexity_region.first, low_complexity_region.second - low_complexity_region.first) << "|" << seq->source->substr(low_complexity_region.second + 5, 5) << endl;
                }

                i = filtered_out->back().second;
                ::memset(amount_array, 0, sizeof(int) * slice_indexes_amount);
            }
        }
    }

    int summary = 0;

    for (pair<int, int> p : *filtered_out)
    {
        for (int i = p.first; i < p.second; i++)
        {
            seq->source->at(i) = tolower(seq->source->at(i));
        }
        summary += p.second - p.first;
    }

    cout << summary << endl;

    delete filtered_out;
};
