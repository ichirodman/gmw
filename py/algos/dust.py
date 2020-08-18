def dust(seq: str, min_len: int = 7, min_score=2.5, threshold_score_difference=0.7, n_chars=False, print_progress=False):
    _to_cut = list()
    _l = min_len - 2
    _amount = [0] * (4 ** 3)
    _i = 0
    while _i + 3 < len(seq):
        print_progress and print('done : {:.2f}%'.format(100 * float(_i) / len(seq)))
        _amount[_get_slice_index(seq[_i:_i + 3])] += 1
        if _i > _l:
            _amount[_get_slice_index(seq[_i - _l:_i - _l + 3])] -= 1
            score = count_dust_score(_amount, _l)
            if score > min_score:
                _add_index = 1
                _add_amount = [0] * (4 ** 3)
                _score_to_compare_with = score
                _new_score = None
                while True:
                    _add_amount[_get_slice_index(seq[_i + _add_index:_i + 3 + _add_index])] += 1
                    _new_score = count_dust_score(_amount, _l, additive_array=_add_amount)
                    # print(_new_score - _score_to_compare_with)
                    if _new_score - _score_to_compare_with < threshold_score_difference:
                        break
                    _score_to_compare_with = _new_score
                    _add_index += 1
                _add_amount[_get_slice_index(seq[_i + _add_index:_i + 3 + _add_index])] -= 1
                _to_cut.append([_i - _l + 1 + 1, _i + 3 + _add_index - 1, _score_to_compare_with])
                # print("add: {}".format(str(_to_cut[-1])))
                # print("{} : {} || {}".format(seq[_i - _l + 1: _i + 3], score, _new_score))
                _i = _to_cut[-1][1]
                _amount = [0] * (4 ** 3)
        _i += 1
    print_progress and print(_to_cut)
    for segment in _to_cut:
        seq = seq[:segment[0]] + (
            seq[segment[0]:segment[1]].lower() if not n_chars else 'N' * (segment[1] - segment[0])) + seq[segment[1]:]
    return seq, _to_cut


def _get_slice_index(seq_slice: str) -> int:
    return sum(int(i) * j for i, j in zip(''.join([str(_get_nucleotide_number(i)) for i in seq_slice]), [16, 4, 1]))


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


def count_dust_score(occurrence_array: list, l_value: int, additive_array: list = None) -> int:
    if not additive_array:
        return sum([(i * (i + 1)) / 2. for i in occurrence_array if i != 0]) / float(l_value - 1)
    else:
        return sum([((i + j) * (i + 1 + j)) / 2. for i, j in zip(occurrence_array, additive_array)]) / float(
            l_value - 1)
