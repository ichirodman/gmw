from algos.rle import rle
from algos.nucletide_hoffman import nucleotide_hoffman, inverse_nucleotide_hoffman

string = "ACTCGAATTT"
rle_string = rle(string)
encoded = nucleotide_hoffman(rle_string)
decoded = inverse_nucleotide_hoffman(encoded)
print('Input :   {}\nRLE :     {}\nHoffman : {}\nInverse : {}\nMatched : {}'.format(
    string, rle_string, encoded, decoded, string == decoded))
