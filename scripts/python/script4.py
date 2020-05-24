# FUENTE: http://rosalind.info/problems/revc/solutions/?page=3
import time
import sys

def getSeqRev(s):
    s_temp = ''
    for i in s:
        if i == 'A':
            s_temp += 'T'
        elif i == 'G':
            s_temp += 'C'
        elif i == 'C':
            s_temp += 'G'
        elif i == 'T':
            s_temp += 'A'
        else:
            s_temp += 'N'
    #print s_temp[::-1]

start_time = time.time()
file =open(sys.argv[1],'r')
getSeqRev(file.read())
print("--- %s seconds  for %s --- \n" % (time.time() - start_time, sys.argv[1]))