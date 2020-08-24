nucleotide_code = {'A': 0, 'C': 1, 'G': 2, 'T': 3}


def encode_slice(seq_slice: str) -> int:
    return sum([(4 ** (len(seq_slice) - _i - 1)) * nucleotide_code[seq_slice[_i]] for _i in range(len(seq_slice))])
