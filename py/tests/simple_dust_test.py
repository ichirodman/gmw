from py.algos.dust import dust

seq = 'AAAACATATTTTTTTGAGTGGGAATTTTGTAAAAAAAATTCATTCAAACCCCCCCCCCCTCCCCCTCGGTTATGTTATTAT'
dusted = dust(seq)
print('\t'.join(dusted))
print('\t'.join(seq))
print('\t'.join([str(i) for i in range(len(seq))]))
print()
print(seq)
print(dusted)
