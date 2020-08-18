def encode_nucleotides(nucl_seq: str) -> int:
    return sum([
        (4 ** (len(nucl_seq) - _i - 1)) * (
            0 if nucl_seq[_i] == 'A' else (
                1 if nucl_seq[_i] == 'C' else (
                    2 if nucl_seq[_i] == 'G' else 3  # for 'T'
                )
            )) for _i in range(len(nucl_seq))
    ])
