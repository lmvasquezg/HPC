# FUENTE: https://gist.github.com/hurshd0/3d54301cdb052cc4c103a2d118a9c7b9

#!/usr/bin/env python3
"""
Description: Python reverese complement program that prompts user to input
valid DNA sequence, only exits when invalid character is entered.
"""
# Add functions here
import time
import sys

def is_seq_valid(seq):
    """Returns True if sequence is DNA otherwise False"""
    valid_bases = ['A', 'T', 'G', 'C']
    for base in seq:
        if base not in valid_bases:
            return False
    return True


def reverse(seq):
    """Returns a reversed string"""
    return seq[::-1]


def complement(seq):
    """Returns a complement DNA sequence"""
    complement_dict = {'A': 'T', 'C': 'G', 'T': 'A', 'G': 'C','\n':''}
    seq_list = list(seq)
    # I can think of 3 ways to do this but first is faster I think ???
    # first list comprehension
    seq_list = [complement_dict[base] for base in seq_list]
    # second complicated lambda
    # seq_list = list(map(lambda base: complement_dict[base], seq_list))
    # third easy for loop
    # for i in range(len(seq_list)):
    #    seq_list[i] = complement_dict[seq_list[i]]
    return ''.join(seq_list)


def reverse_complement(seq):
    """"Returns a reverse complement DNA sequence"""
    seq = reverse(seq)
    seq = complement(seq)
    return seq

# Main starts here


def main():
    start_time = time.time()
    file =open(sys.argv[1],'r')
    reverse_complement(file.read())
    print("--- %s seconds  for %s --- \n" % (time.time() - start_time, sys.argv[1]))


if __name__ == '__main__':
    main()