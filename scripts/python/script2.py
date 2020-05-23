# FUENTE: https://github.com/kaniick/Rosalind/blob/master/Bioinformatics%20Stronghold/Complementing%20a%20Strand%20of%20DNA%20(REVC)

def reversecomp(dna):
  reversedna = dna[::-1]
  complement = reversedna.replace('A','t').replace('T','a').replace('G','c').replace('C','g').upper()
  return complement
