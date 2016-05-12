import numpy as np
from cStringIO import StringIO 

def hitrate():
	#txt = open(nombre).read()
	txt = open('tests/fold10.in_hit_rates').read()
	vector = np.loadtxt(StringIO(txt),
				delimiter='\n',
	      		dtype=float)
	std = np.std(vector)
	mean = np.mean(vector)
	print std
	print mean
	
	return