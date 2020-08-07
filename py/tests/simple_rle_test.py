from py.algos.rle import rle, inverse_rle

string = 'ABCABCABCDDDFFFFFF'
encoded = rle(string)
decoded = inverse_rle(encoded)
print('Input :   {}\nRLE :     {}\nInverse : {}\nMatched : {}'.format(
    string, encoded, decoded, string == decoded))
