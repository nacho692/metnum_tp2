import numpy as np
import matplotlib.pyplot as plt

random = ''
fold = 'fold.in'
dataDir = '../../data'

vecinos = 5;
alpha = 50;
dimPLS_DA = 10;
kFold = 10;

data = np.loadtxt(dataDir + '/train.csv',dtype='string')
data = data[1:len(data)]

if random == '':
	rango = np.arange(len(data))
	np.random.shuffle(rango)
	np.savetxt('random.txt',rango, fmt="%d")
else:
      rango = np.loadtxt(random,dtype='int',delimiter='\n')

foldLen = int(len(data)/kFold)

f = open(fold,'w')
header = dataDir + ' ' + str(vecinos) + ' ' + str(alpha) + ' ' + str(dimPLS_DA) + ' ' + str(kFold) + '\n'
f.write(header)
for i in range(0,kFold):
	#i es el fold de test
	for j in range(0,len(data)):
		if i*foldLen <= rango[j] < (i+1)*foldLen:
			f.write('0 ')
		else:
			f.write('1 ')
	f.write('\n');
f.close()


#ARCHIVO CREADOS
#ACA HAY QUE HACER LO QUE SE TENGA QUE HACER

# df_confusion = [[33,2,0,0,0,0,0,0,0,1,3], 
#             	[3,31,0,0,0,0,0,0,0,0,0], 
#             	[0,4,41,0,0,0,0,0,0,0,1], 
#             	[0,1,0,30,0,6,0,0,0,0,1], 
#             	[0,0,0,0,38,10,0,0,0,0,0], 
#             	[0,0,0,3,1,39,0,0,0,0,4], 
#             	[0,2,2,0,4,1,31,0,0,0,2],
#             	[0,1,0,0,0,0,0,36,0,2,0], 
#             	[0,0,0,0,0,0,1,5,37,5,1], 
#             	[3,0,0,0,0,0,0,0,0,39,0], 
#             	[0,0,0,0,0,0,0,0,0,0,38]]

# fig = plt.figure()
# plt.clf()
# ax = fig.add_subplot(111)
# res = ax.imshow(np.array(df_confusion),cmap =plt.cm.jet, interpolation='nearest')

# cb = fig.colorbar(res)
#plt.show()


