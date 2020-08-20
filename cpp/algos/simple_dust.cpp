#include "simple_dust.hpp"

using namespace std;

// DEBUG FUNCTION
void print_arr(int *arr, int len)
{
    for (int i = 0; i < len; i++)
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
    const int slice_length = slice.length();
    int code = 0;
    for (int i = 0; i < slice_length; i++)
    {
        code += get_nucleotide_index(slice[i]) * pow(4, slice_length - i - 1);
    }
    return code;
};

float count_subseq_score(int *occurrence_array, int array_length, int *additive_array = nullptr)
{
    float sum_score = 0.0;
    int slices_amount = 0;
    for (int i = 0; i < array_length; i++)
    {
        int occurrence_i_value = occurrence_array[i] + (additive_array == nullptr ? 0 : additive_array[i]);
        slices_amount += occurrence_i_value;
        sum_score += static_cast<float>(occurrence_i_value * (occurrence_i_value + 1)) / 2.0;
    }
    return static_cast<float>(sum_score) / (static_cast<float>(slices_amount) - 1.0);
}

void dust(FastaSequence const *seq, int min_len, float score_increase_threshold,
          float threshold_score_difference, bool print_progress, bool debug)
{
    const int slice_len = 3, slices_amount = min_len - 2, slice_indexes_amount = static_cast<int>(pow(4, slice_len));

    int amount_array[slice_indexes_amount];
    ::memset(amount_array, 0, sizeof(int) * slice_indexes_amount);

    vector<pair<int, int>> *filtered_out = new vector<pair<int, int>>();

    for (int i = 0, seq_len = seq->source.length(), done = 0; i + slice_len < seq_len; i++)
    {
        if (print_progress && static_cast<int>(round((i + 1) * 100.0 / (seq_len - slice_len))) > done)
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
            print_arr(amount_array, slice_indexes_amount);
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
                    const string slice_out_of_bounds = seq->source.substr(i + additive_i - 1, slice_len);
                    const int slice_out_of_bounds_index = get_slice_index(slice_out_of_bounds);
                    additive_amount_array[slice_out_of_bounds_index]++;

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
                    cout << low_complexity_region.first << "->" << low_complexity_region.second << " : " << seq->source.substr(low_complexity_region.first - 5, 5) << "|"
                         << seq->source.substr(low_complexity_region.first, low_complexity_region.second - low_complexity_region.first) << "|" << seq->source.substr(low_complexity_region.second + 5, 5) << endl;
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
            seq->source[i] = tolower(seq->source[i]);
        }
        summary += p.second - p.first;
    }

    cout << summary << endl;

    delete filtered_out;
};
