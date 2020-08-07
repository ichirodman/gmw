from py.utils.fasta import extract_fasta
from py.algos.simple_bwt import bwt, inverse_bwt
from time import time

_string_to_encode = extract_fasta('CP003305.1.fasta')[0]['data'][:2000]

_start_time_1 = time()
encoded = bwt(_string_to_encode)
_end_time_1 = time()

_start_time_2 = time()
decoded = inverse_bwt(encoded)
_end_time_2 = time()

print(encoded)
print('{:.5f}'.format(_end_time_1 - _start_time_1))

print(decoded)
print('{:.3f}'.format(_end_time_2 - _start_time_2))
