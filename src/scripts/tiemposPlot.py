import numpy as np
import matplotlib.pyplot as plt
from cStringIO import StringIO 

txt = open('resultados_alpha.txt', 'r').read() 

# alphas = np.loadtxt(
# 	StringIO(txt.replace("Alpha: ",''))	,
# dtype = int)
a = np.array([25385, 25343, 25423, 25557, 25546, 25542, 25531, 25534, 25312, 25347])
mean = np.mean(a)
b = np.std(a)

print "Std:"
print b 
print "Mean:"
print mean