# FUENTE: https://www.biostars.org/p/90/

#
# Reverse complement example with BioPython
#

from Bio.Seq import Seq

# a separate function to reverse strings (or other iterables)
def rev(it):
    "Reverses an interable and returns it as a string"
    return ''.join(reversed(it))

# create a Seq class instance
dna = Seq("ATGGCCATTGTAATGGGCCGCTGAAAGGGTGCCCGATAG")

# original DNA
print(type(dna))
print(dna)

# reverse complement DNA, returns a new sequence
print(dna.reverse_complement())

# currently there is no direct way to just reverse a sequence
# we need to do a little extra work

rseq = rev(str(dna))
rdna = Seq(rseq)

# reversed sequence
print(rdna)

# to complement DNA, returns a new sequence
print(dna.complement())