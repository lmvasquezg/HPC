# FUENTE: https://codereview.stackexchange.com/questions/151329/reverse-complement-of-a-dna-string
import time
import sys

def reverse_complement(dna):
    complement = {'A': 'T', 'C': 'G', 'G': 'C', 'T': 'A','\n':''}
    return ''.join([complement[base] for base in dna[::-1]])

start_time = time.time()
file =open(sys.argv[1],'r')
reverse_complement(file.read())
print("--- %s seconds  for %s --- \n" % (time.time() - start_time, sys.argv[1]))