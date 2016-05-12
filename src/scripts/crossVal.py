import numpy as np
import matplotlib.pyplot as plt


def kFold(header, tSetLen, K=10, output='fold.out', seed=0):
	np.random.seed(int(seed))
	rango = np.arange(tSetLen)
	np.random.shuffle(rango)

	foldLen = tSetLen/K

	f = open(output,'w')
	f.write(header + '\n')
	for i in range(0,K):
		#i es el fold de test
		for j in range(0,tSetLen):
			if i*foldLen <= rango[j] < (i+1)*foldLen:
				f.write('0 ')
			else:
				f.write('1 ')
		f.write('\n');
	f.close()
	return
