from py.utils.fasta import extract_fasta
import matplotlib.pyplot as plt

SLICE_LEN = 5
nucleotide_code = {'A': 0, 'C': 1, 'G': 2, 'T': 3}


def encode_slice(seq_slice: str) -> int:
    return sum([(4 ** (len(seq_slice) - i - 1)) * nucleotide_code[seq_slice[i]] for i in range(len(seq_slice))])


occurrence1, occurrence2 = [list() for _ in range(len(nucleotide_code.keys()) ** SLICE_LEN)], \
                           [list() for _ in range(len(nucleotide_code.keys()) ** SLICE_LEN)]

for seq, array in zip(
        [extract_fasta('small/source.fasta')[0]['data'], extract_fasta('small/deletion.fasta')[0]['data']],
        [occurrence1, occurrence2]):
    for i in range(len(seq) - SLICE_LEN):
        array[encode_slice(seq[i:i + SLICE_LEN])].append(i)

print('Occurrences done')

points_x, point_y = list(), list()

for o1, o2 in zip(occurrence1, occurrence2):
    for i1 in o1:
        for i2 in o2:
            points_x.append(i1)
            point_y.append(i2)

plt.scatter(points_x, point_y, s=1)
plt.show()
