# FUENTE: https://github.com/niltoncsr/rosalind/blob/master/complementing-a-strand-of-dna.py
import sys
import time
start_time = time.time()

file =open(sys.argv[1], 'r')
s = file.read()
sc = ''

for nt in s:
	if nt == 'A': nt = 'T'
	elif nt == 'T': nt = 'A'
	elif nt == 'G': nt = 'C'
	elif nt == 'C': nt = 'G'
	sc += nt

i_sc = sc[::-1]
print("--- %s seconds  for %s--- \n" % (time.time() - start_time, sys.argv[1]))
