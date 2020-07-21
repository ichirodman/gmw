from datetime import datetime
from utils import execute_fasta

# Do not rename or delete
# This's used in alignment functions
seq1, seq2 = None, None

data = execute_fasta('../data/task1_sequences.fasta')

r = datetime.now()

# Re-definition
seq1, seq2 = data[0]['val'], data[1]['val']

print(seq1[:120])
print(seq2[:120])

test = execute_fasta('../data/CP000766.3.fasta')[0]['val']

i = 0
while i < len(test):
    i += 1
print(len(test))
print(datetime.now() - r)
