from py.algos.swa import swa
from py.algos.dust import dust

s1 = 'ACCTGCACATTGTGCACATGTACCCAAAAAAAAAGCGCGCGCGCGTTTTTTTACAGTATGAAAAAAAAAAAAACCCCACTCCTGG'
s2 = 'ACCTGCACATTGTGCACATGTACCCACAGTATCCTGCACATTGGCTTTTTTTACAGTATGACAGTATGACAGTCCCCACTCCTGG'

print(s1)
s1 = dust(s1)[0]
print(s1)
print(s2)
s2 = dust(s2)[0]
print(s2)

print(str(swa(s1, s2)).replace(')', '').replace('(', '').replace(', ', '\n').replace('\'', ''))
