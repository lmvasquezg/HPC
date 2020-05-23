# FUENTE: https://codereview.stackexchange.com/questions/151329/reverse-complement-of-a-dna-string

def reverse_complement(dna):
    complement = {'A': 'T', 'C': 'G', 'G': 'C', 'T': 'A'}
    return ''.join([complement[base] for base in dna[::-1]])