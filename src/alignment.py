import matplotlib.pyplot as plt

from datetime import datetime
from utils import execute_fasta

NUCLEOTIDES_MATCHING_MIN_AMOUNT = 17
SINGLE_REPLACEMENTS_MAX_AMOUNT = 1

# Do not rename or delete
# This's used in alignment functions
seq1, seq2 = None, None

data = execute_fasta('../data/task1_sequences.fasta')

# Re-definition
seq1, seq2 = data[1]['val'], data[2]['val']

# seq1, seq2 = execute_fasta('../data/CP003305.1.fasta')[0]['val'], execute_fasta('../data/CP000766.3.fasta')[0]['val']
# seq1, seq2 = seq1[int(1e+6):], seq2[int(1e+6):]

start_time = datetime.now()


def min_match(start1: int, start2: int, reverse1=False, reverse2=False):
    global seq1, seq2, NUCLEOTIDES_MATCHING_MIN_AMOUNT, SINGLE_REPLACEMENTS_MAX_AMOUNT
    _error = 0
    if seq1[start1] != seq2[start2]:
        return False
    for _i in range(1, NUCLEOTIDES_MATCHING_MIN_AMOUNT):
        if seq1[start1 + (_i if not reverse1 else - _i)] != seq2[start2 + (_i if not reverse2 else - _i)]:
            _error += 1
        if _error > SINGLE_REPLACEMENTS_MAX_AMOUNT:
            break
        '''print('_i: {}  _i1: {}  _i2: {}  n1: {}  n2: {}'.format(_i, start1 + (_i if not reverse1 else - _i),
                                                                start2 + (_i if not reverse2 else - _i),
                                                                seq1[start1 + (_i if not reverse1 else - _i)],
                                                                seq2[start2 + (_i if not reverse2 else - _i)]))'''
    return not _error > SINGLE_REPLACEMENTS_MAX_AMOUNT


def prolong(start1: int, start2: int, reverse1=False, reverse2=False):
    global seq1, seq2, NUCLEOTIDES_MATCHING_MIN_AMOUNT, SINGLE_REPLACEMENTS_MAX_AMOUNT
    _error, _i, _i1, _i2 = 0, 0, start1, start2
    while 0 <= _i1 < len(seq1) and 0 <= _i2 < len(seq2):
        if seq1[_i1] != seq2[_i2]:
            _error += 1
        if _error > SINGLE_REPLACEMENTS_MAX_AMOUNT:
            break
        _i1 += 1 if not reverse1 else - 1
        _i2 += 1 if not reverse2 else - 1
        # print('_i1: {}  _i2: {}'.format(_i1, _i2))
    return [_i1, _i2]


def used(_i: int, _j: int):
    global coincidences
    for c in coincidences:
        if (c[0][0] <= _i <= c[0][1] or c[0][0] >= _i >= c[0][1]) and \
                (c[1][0] <= _j <= c[1][1] or c[1][0] >= _j >= c[1][1]):
            return True
    return False


# print('seq1: {}  \nseq2: {}'.format(seq1[28:48], seq2[214410:214430]))
# [... [[x1, x2], [y1, y2]] ...]
coincidences = list()

try:
    plt.plot([0, len(seq1)], [0, len(seq2)], marker='x')
    for i in range(0, len(seq1), NUCLEOTIDES_MATCHING_MIN_AMOUNT):
        print(i)
        j = 0
        while j < len(seq2) - NUCLEOTIDES_MATCHING_MIN_AMOUNT:
            if not used(i, j):
                for k1 in [False, True]:
                    for k2 in [False, True]:
                        if min_match(i, j, k1, k2):
                            # print('i: {}  j: {}  k1: {}  k2: {}'.format(i, j, k1, k2))
                            # print(coincidences)
                            p = prolong(i, j, k1, k2)
                            # print('prolong: {}'.format(p))
                            # print('-------------')
                            plt.plot([i, p[0]], [j, p[1]], marker='o')
                            coincidences.append([[i, p[0]], [j, p[1]]])
            j += 1
finally:
    print('time: {}'.format(datetime.now() - start_time))
    plt.show()
