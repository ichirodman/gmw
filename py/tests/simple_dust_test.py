from py.algos.dust import dust
from py.utils.fasta import extract_fasta

# seq = extract_fasta('CP003305.1.fasta')[0]['data']
seq = 'AAAACATATTTTTTTGTTTTTTTTTAGTGGGAATTTTGTAAAAAAAATTCATTCAAACCCCCCCCCCCTCCCCCTCGGTTATGTTATTAT'
dusted, cut = dust(seq, n_chars=True)

print('\t'.join(dusted))
print('\t'.join(seq))
print('\t'.join([str(i) for i in range(len(seq))]))
print()
print(seq)
print(dusted)

exit()
for k in cut:
    print('\n{}\n{}'.format(seq[k[0] - 3:k[1] + 3], '-' * 3 + dusted[k[0]: k[1]] + '-' * 3))
