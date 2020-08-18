def dust(seq: str, min_len: int = 7, score_increase_threshold=2.5, threshold_score_difference=0.7, n_chars=False,
         print_progress=False):
    __slice_len = 3
    __to_filter_out, __amount_array = list(), [0] * (4 ** __slice_len)
    __i, __slices_amount = 0, min_len - 2
    __seq_len = len(seq)
    __done = 0

    while __i + __slice_len < __seq_len:
        if print_progress and round((__i + __slice_len) * 100. / __seq_len) > __done:
            __done = int(round((__i + 1) * 100. / (__seq_len - __slice_len)))
            # print('__done : {}%'.format(__done))

        __amount_array[_get_slice_index(seq[__i:__i + __slice_len])] += 1
        
        if __i > __slices_amount:
            __amount_array[_get_slice_index(seq[__i - __slices_amount:__i - __slices_amount + __slice_len])] -= 1
            __sub_seq_score = _count_dust_score(__amount_array, __slices_amount)
            
            if __sub_seq_score > score_increase_threshold:
                __additive_i = 1
                __additive_amount_array = [0] * (4 ** __slice_len)
                __score_to_compare_with = __sub_seq_score
                __new_score = list()
                while True:
                    __additive_amount_array[_get_slice_index(seq[__i + __additive_i:__i + __slice_len + __additive_i])] += 1
                    __new_score.append(_count_dust_score(__amount_array, __slices_amount, additive_array=__additive_amount_array))
                    print_progress and print(
                        'scores difference: {}'.format(__new_score[-1] - __score_to_compare_with))
                    if len(__new_score) > 3:
                        if __new_score[-1] - __score_to_compare_with < threshold_score_difference:
                            break
                        __score_to_compare_with = __new_score[-1]
                    __additive_i += 1
                __additive_amount_array[_get_slice_index(seq[__i + __additive_i:__i + __slice_len + __additive_i])] -= 1
                __to_filter_out.append([__i - __slices_amount + 1 + 1, __i + __slice_len + __additive_i - 1, __score_to_compare_with])
                print_progress and print("add: {}".format(str(__to_filter_out[-1])))
                print_progress and print("{} : {} || {}".format(seq[__i - __slices_amount + 1: __i + __slice_len], __sub_seq_score, __new_score))
                __i = __to_filter_out[-1][1]
                __amount_array = [0] * (4 ** __slice_len)
                
        __i += 1
        
    print_progress and print(__to_filter_out)
    for segment in __to_filter_out:
        seq = seq[:segment[0]] + (
            seq[segment[0]:segment[1]].lower() if not n_chars else 'N' * (segment[1] - segment[0])
        ) + seq[segment[1]:]
    return seq, __to_filter_out


def _get_slice_index(seq_slice: str) -> int:
    return sum(int(i) * j for i, j in zip(''.join([str(_get_nucleotide_number(i)) for i in seq_slice]),
                                          [2 ** i for i in range(len(seq_slice))]))


def _get_nucleotide_number(nucleotide: str) -> int:
    if nucleotide == 'A':
        return 0
    elif nucleotide == 'C':
        return 1
    elif nucleotide == 'G':
        return 2
    elif nucleotide == 'T':
        return 3
    else:
        raise "Something strange: {}".format(nucleotide)


def _count_dust_score(occurrence_array: list, __slices_amount: int, additive_array: list = None) -> int:
    if not additive_array:
        return sum([(i * (i + 1)) / 2. for i in occurrence_array if i != 0]) / float(__slices_amount - 1)
    else:
        return sum([((i + j) * (i + 1 + j)) / 2. for i, j in zip(occurrence_array, additive_array)]) \
               / float(__slices_amount - 1)
