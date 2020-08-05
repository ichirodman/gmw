def nucleotide_hoffman(rle_encoded_string: str):
    rle_encoded_string = rle_encoded_string.upper()
    i = 0
    encoded = ''
    encoding = {'A': '00', 'C': '01', 'G': '10', 'T': '11'}
    while i < len(rle_encoded_string):
        index = ''
        while rle_encoded_string[i] == '-' or rle_encoded_string[i].isdigit():
            index += rle_encoded_string[i]
            i += 1
        index = int(index)
        if index > 0:
            encoded += index * encoding[rle_encoded_string[i]]
            i += 1
        else:
            for char in rle_encoded_string[i:i + abs(index)]:
                encoded += encoding[char]
            i += abs(index)
    return int('1' + encoded, 2)


def inverse_nucleotide_hoffman(code: int):
    decoding = {'00': 'A', '01': 'C', '10': 'G', '11': 'T'}
    code = bin(code)[3:]
    decoded = ''
    for i in range(0, len(code), 2):
        decoded += decoding[code[i: i + 2]]
    return decoded
