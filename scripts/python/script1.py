# FUENTE: https://github.com/niltoncsr/rosalind/blob/master/complementing-a-strand-of-dna.py
import sys
import time

list = ['804','989','6000','10000','973470','1162062','1385802','3005381','5927724','7765758','8285706','11320749','12154329','15714072','19403505']
for x in list:
	start_time = time.time()
	filename = '../../datasets/dataset_'+x+'.txt'
	file =open(filename, 'r')
	s = file.read()
	sc = ''

	for nt in s:
		if nt == 'A': nt = 'T'
		elif nt == 'T': nt = 'A'
		elif nt == 'G': nt = 'C'
		elif nt == 'C': nt = 'G'
		sc += nt

	i_sc = sc[::-1]
	print("--- %s seconds  for %s bases--- \n" % (time.time() - start_time, x))
	file.close()
