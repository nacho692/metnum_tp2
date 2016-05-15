import numpy as np
import matplotlib.pyplot as plt
from cStringIO import StringIO 
import pylab

#txt = open('resultados_alpha.txt', 'r').read() 

# alphas = np.loadtxt(
# 	StringIO(txt.replace("Alpha: ",''))	,
# dtype = int)
alphas = np.array([20,40,60,80])
vecinos = np.array([2,3,4,5,6,7,8,9,10,15,50,100,1000,10000,37000])
alpha20 = np.array([[ 0.967381, 0.967857, 0.970476, 0.962619, 0.963095, 0.957381, 0.962143, 0.96619, 0.965714, 0.965952],
						[ 0.97119, 0.97119, 0.972619, 0.969048, 0.969048, 0.963333, 0.964762, 0.968333, 0.968095, 0.968095],
						[ 0.972143, 0.972381, 0.974048, 0.968571, 0.97, 0.965476, 0.966429, 0.969762, 0.969048, 0.968333],
						[ 0.971667, 0.970714, 0.972143, 0.969048, 0.967619, 0.96619, 0.965476, 0.969524, 0.96881, 0.967143],
						[ 0.971429, 0.971667, 0.973333, 0.968571, 0.969762, 0.965952, 0.966905, 0.97, 0.969048, 0.966667],
						[ 0.968333, 0.969286, 0.970476, 0.968571, 0.968333, 0.964048, 0.964286, 0.967857, 0.967619, 0.96619],
						[ 0.969524, 0.969286, 0.972619, 0.968095, 0.969286, 0.965714, 0.964762, 0.97119, 0.966429, 0.966667],
						[ 0.966429, 0.966905, 0.970238, 0.966429, 0.968333, 0.963095, 0.964524, 0.969524, 0.966667, 0.964524],
						[ 0.968333, 0.966667, 0.97119, 0.965476, 0.968095, 0.962857, 0.965, 0.970476, 0.966429, 0.965952],
						[ 0.963571, 0.965952, 0.966429, 0.965, 0.965714, 0.960238, 0.961429, 0.965952, 0.965476, 0.962381],
						[ 0.957381, 0.956429, 0.956667, 0.951429, 0.954048, 0.949524, 0.950952, 0.952857, 0.954048, 0.95119],
						[ 0.952143, 0.943333, 0.947143, 0.94381, 0.943333, 0.941429, 0.940714, 0.94619, 0.946429, 0.942619],
						[ 0.896905, 0.897143, 0.890714, 0.890714, 0.891905, 0.882857, 0.889524, 0.891905, 0.893333, 0.890714],
						[ 0.74381, 0.744048, 0.725, 0.735, 0.734286, 0.724524, 0.73881, 0.735238, 0.734048, 0.735],
						[ 0.69381, 0.703095, 0.675476, 0.681905, 0.686429, 0.682143, 0.68881, 0.688095, 0.694762, 0.682857]]
)
alpha40 = np.array([[ 0.972857, 0.97381, 0.975476, 0.972381, 0.971905, 0.967143, 0.97381, 0.974286, 0.975, 0.973571],
						[ 0.975, 0.973095, 0.977381, 0.975952, 0.974286, 0.969048, 0.975238, 0.975952, 0.976667, 0.975952],
						[ 0.976667, 0.975952, 0.979048, 0.975952, 0.977143, 0.971905, 0.976905, 0.977857, 0.975952, 0.975714],
						[ 0.975714, 0.974762, 0.97619, 0.974524, 0.975714, 0.972381, 0.976667, 0.975952, 0.974524, 0.975],
						[ 0.976429, 0.975476, 0.978333, 0.975238, 0.977381, 0.973571, 0.975952, 0.976905, 0.974286, 0.975952],
						[ 0.975476, 0.97381, 0.974524, 0.973333, 0.976429, 0.972857, 0.974762, 0.975, 0.973095, 0.973095],
						[ 0.97619, 0.974286, 0.975476, 0.974762, 0.976429, 0.970714, 0.973333, 0.976667, 0.973571, 0.975],
						[ 0.974048, 0.97119, 0.973333, 0.972857, 0.975714, 0.969048, 0.971905, 0.977143, 0.973333, 0.97119],
						[ 0.974048, 0.972619, 0.974762, 0.971905, 0.974762, 0.97, 0.971429, 0.976667, 0.974048, 0.972381],
						[ 0.97, 0.97119, 0.970238, 0.96881, 0.969762, 0.968571, 0.966667, 0.969762, 0.969762, 0.97],
						[ 0.96119, 0.958571, 0.96, 0.95881, 0.958333, 0.955, 0.958571, 0.957381, 0.958333, 0.957381],
						[ 0.952143, 0.949048, 0.952619, 0.949286, 0.947143, 0.945952, 0.949048, 0.946905, 0.947619, 0.946667],
						[ 0.891667, 0.895, 0.884762, 0.884048, 0.887381, 0.87619, 0.889524, 0.880476, 0.88881, 0.88381],
						[ 0.695238, 0.700238, 0.675, 0.686905, 0.690476, 0.681429, 0.684524, 0.694762, 0.686905, 0.686905],
						[ 0.593333, 0.612143, 0.571905, 0.574286, 0.575476, 0.578095, 0.579524, 0.589286, 0.602381, 0.573333]]
)

alpha60 = np.array([[ 0.972381, 0.972857, 0.977143, 0.970714, 0.973571, 0.967857, 0.974524, 0.972857, 0.973095, 0.975714],
						[ 0.975714, 0.973095, 0.975714, 0.973095, 0.974524, 0.97119, 0.975952, 0.973095, 0.973095, 0.975],
						[ 0.977143, 0.975238, 0.977143, 0.975, 0.975476, 0.971905, 0.976905, 0.975952, 0.974048, 0.976429],
						[ 0.976667, 0.973095, 0.976667, 0.975714, 0.975476, 0.973095, 0.975238, 0.975476, 0.973095, 0.975238],
						[ 0.975714, 0.973571, 0.975476, 0.975238, 0.975, 0.97381, 0.976429, 0.974524, 0.972857, 0.974524],
						[ 0.975238, 0.971905, 0.97381, 0.973333, 0.975476, 0.972619, 0.975476, 0.973095, 0.971667, 0.972857],
						[ 0.974762, 0.971905, 0.972857, 0.975, 0.975, 0.972857, 0.974762, 0.974048, 0.970714, 0.973333],
						[ 0.974524, 0.97119, 0.971667, 0.972619, 0.971667, 0.970476, 0.972857, 0.973333, 0.970714, 0.971905],
						[ 0.974524, 0.971429, 0.971667, 0.972857, 0.973095, 0.970714, 0.974048, 0.974762, 0.969048, 0.973571],
						[ 0.969762, 0.969524, 0.969286, 0.96881, 0.968095, 0.967619, 0.970476, 0.969762, 0.96881, 0.969048],
						[ 0.96119, 0.955952, 0.957857, 0.955952, 0.955714, 0.953571, 0.956667, 0.954286, 0.955714, 0.955],
						[ 0.950714, 0.946667, 0.94881, 0.945714, 0.944048, 0.940714, 0.945952, 0.942619, 0.944048, 0.944048],
						[ 0.88381, 0.88619, 0.87381, 0.873571, 0.876667, 0.86381, 0.878333, 0.871429, 0.880952, 0.873333],
						[ 0.661667, 0.666667, 0.645, 0.655714, 0.662381, 0.654524, 0.652143, 0.660476, 0.663095, 0.657619],
						[ 0.54119, 0.559048, 0.509048, 0.514524, 0.51619, 0.518571, 0.51881, 0.523333, 0.548571, 0.507857]]
)

alpha80 = np.array([[ 0.970238, 0.971905, 0.974524, 0.970952, 0.969286, 0.968095, 0.972857, 0.972619, 0.971905, 0.974286],
						[ 0.975952, 0.971429, 0.975, 0.973333, 0.973095, 0.969524, 0.97619, 0.973571, 0.97119, 0.973333],
						[ 0.97619, 0.973095, 0.976667, 0.975952, 0.97381, 0.969524, 0.975714, 0.974524, 0.972143, 0.974524],
						[ 0.974286, 0.972143, 0.973571, 0.97381, 0.972857, 0.971667, 0.975476, 0.974524, 0.971667, 0.974524],
						[ 0.975238, 0.974286, 0.974762, 0.974762, 0.974048, 0.972619, 0.975952, 0.975, 0.970714, 0.974048],
						[ 0.973571, 0.97119, 0.971905, 0.972381, 0.973095, 0.972619, 0.972619, 0.972857, 0.97119, 0.972619],
						[ 0.974286, 0.971429, 0.971905, 0.973333, 0.973571, 0.972619, 0.973333, 0.97381, 0.970952, 0.973333],
						[ 0.973333, 0.970476, 0.970476, 0.97119, 0.970714, 0.97, 0.972143, 0.97119, 0.969762, 0.970476],
						[ 0.974048, 0.970714, 0.970238, 0.971905, 0.970476, 0.967619, 0.970714, 0.971905, 0.969524, 0.970714],
						[ 0.969762, 0.969048, 0.967381, 0.968333, 0.965952, 0.965714, 0.969286, 0.967381, 0.966667, 0.967143],
						[ 0.95881, 0.953571, 0.95619, 0.953571, 0.953095, 0.95, 0.954048, 0.95119, 0.953333, 0.95381],
						[ 0.948333, 0.944048, 0.946429, 0.942381, 0.939762, 0.939762, 0.943095, 0.93881, 0.941429, 0.94119],
						[ 0.874048, 0.878333, 0.865476, 0.868333, 0.869762, 0.855714, 0.870714, 0.864286, 0.871905, 0.866429],
						[ 0.643571, 0.649762, 0.620238, 0.634762, 0.639048, 0.636667, 0.634048, 0.640952, 0.643333, 0.636429],
						[ 0.501905, 0.527381, 0.476429, 0.482619, 0.481429, 0.484048, 0.485476, 0.48881, 0.51381, 0.475238]]
)

devilalpha20 = np.empty(len(vecinos))
devilalpha40 = np.empty(len(vecinos))
devilalpha60 = np.empty(len(vecinos))
devilalpha80 = np.empty(len(vecinos))
meanalpha20 = np.empty(len(vecinos))
meanalpha40 = np.empty(len(vecinos))
meanalpha60 = np.empty(len(vecinos))
meanalpha80 = np.empty(len(vecinos))
for i in range(0,len(vecinos)):
	devilalpha20[i] = np.std(alpha20[i])
	meanalpha20[i] = np.mean(alpha20[i])
	devilalpha40[i] = np.std(alpha40[i])
	meanalpha40[i] = np.mean(alpha40[i])
	devilalpha60[i] = np.std(alpha60[i])
	meanalpha60[i] = np.mean(alpha60[i])
	devilalpha80[i] = np.std(alpha80[i])
	meanalpha80[i] = np.mean(alpha80[i])

fig = plt.figure()
ax = fig.add_subplot(111)
ax.set_xlabel("Vecinos", fontsize = 16)
ax.set_ylabel("Hitrate", fontsize = 16)
ax.errorbar(vecinos, meanalpha20, yerr=devilalpha20, color = "r", label='Alpha: 20')
ax.errorbar(vecinos, meanalpha40, yerr=devilalpha40, color = "g", label='Alpha: 40')
ax.errorbar(vecinos, meanalpha60, yerr=devilalpha60, color = "b", label='Alpha: 60')
ax.errorbar(vecinos, meanalpha80, yerr=devilalpha80, color = "coral", label='Alpha: 80')
pylab.legend(loc='upper right')
plt.title('Hitrate PCA', fontsize = 18)

plt.show()