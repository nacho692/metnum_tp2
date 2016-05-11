import subprocess
import os
import random

tset = 784
ks = random.sample(range(1, tset), 60)
alphas = random.sample(range(1, 784), 60)
gammas = random.sample(range(1, 784), 60)

args = ["./tp", "test1.in"]


popen = subprocess.Popen(args,stdout=subprocess.PIPE, stderr=subprocess.PIPE)

out = popen.communicate()

print out

# print "Ks:"
# print ks
# print "Alphas:"
# print alphas
# print "Gammas:"
# print gammas