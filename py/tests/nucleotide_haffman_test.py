from py.algos.rle import rle
from py.algos.nucl_haffman import nucleotide_haffman, inverse_nucleotide_haffman

string = "ACTCGAATTT"
rle_string = rle(string)
encoded = nucleotide_haffman(rle_string)
decoded = inverse_nucleotide_haffman(encoded)
print('Input :   {}\nRLE :     {}\nHoffman : {}\nInverse : {}\nMatched : {}'.format(
    string, rle_string, encoded, decoded, string == decoded))
