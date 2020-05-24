# FUENTE: https://github.com/kaniick/Rosalind/blob/master/Bioinformatics%20Stronghold/Complementing%20a%20Strand%20of%20DNA%20(REVC)
import time 
import sys
def reversecomp(dna):
  reversedna = dna[::-1]
  complement = reversedna.replace('A','t').replace('T','a').replace('G','c').replace('C','g').upper()
  return complement

start_time = time.time()
file =open(sys.argv[1],'r')
reversecomp(file.read())
print("--- %s seconds  for %s --- \n" % (time.time() - start_time, sys.argv[1]))
