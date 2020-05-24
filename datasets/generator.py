import random
import string
 
def randomString(stringLength):
    letters = ['A', 'C', 'G','T']
    return ''.join(random.choice(letters) for i in range(stringLength))
 
f = open("dataset_80000000.txt", "a")
f.write(randomString(80000000))
f.close()