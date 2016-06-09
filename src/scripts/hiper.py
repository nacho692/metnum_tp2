import subprocess
import os
import random
import numpy as np
from cStringIO import StringIO 
from crossVal import *
from confusionPlot import *
import operator

def grafico(i,K,alpha,gamma,vecino,ffile):
	
	txt = open('tests/'+ffile + '_matrices_confusion', 'r').read() 

	matrix = np.loadtxt(
  		StringIO(txt.replace('[', '').replace("]", '')),
  		delimiter=', ',
  		dtype=int)
	pca = np.zeros((K,10), dtype=int)
	pls = np.zeros((K,10), dtype=int)
	for i in range(0,K):
		pca += matrix[i*20:i*20+10]
		pls += matrix[i*20+10:i*20+10+10]

	titulo = 'PCA\n' + 'Alpha: ' + str(alpha) + ' | ' +'Vecinos: ' + str(vecino) + ' | ' + 'Fold: ' + str(K)
	gfile = 'pca_' + str(alpha) + '_' + str(vecino) + '_' + str(K)
	plotConf(pca,titulo,'tests/paramTest/graph/' + gfile + '.png')
	return

def hitratePCA(nombre,K,traduccion):
	#txt = open(nombre).read()
	txt = open(nombre).read()
	vector = np.loadtxt(StringIO(txt),
				delimiter='\n',
	      		dtype=float)
	pca = np.empty(K)
	for i in range(0,K):
		pca[i] = vector[i*2]
		
	stdPCA = np.std(pca)
	meanPCA = np.mean(pca)
	
	print 'Std PCA: ' + str(stdPCA) + ' | ' + 'Mean PCA: ' + str(meanPCA)
	return (stdPCA,meanPCA,traduccion)

def hitratePLS(nombre,K,traduccion):
	#txt = open(nombre).read()
	txt = open(nombre).read()
	vector = np.loadtxt(StringIO(txt),
				delimiter='\n',
	      		dtype=float)
	pls = np.empty(K)
	for i in range(0,K):
		pls[i] = vector[i*2+1]
		
	stdPLS = np.std(pls)
	meanPLS = np.mean(pls)
	
	print 'Std PLS: ' + str(stdPLS) + ' | ' + 'Mean PLS: ' + str(meanPLS)
	return (stdPLS,meanPLS,traduccion)

def paramTest(K,tSet = 42000, seed = 0):	
	np.random.seed(seed)
	alphas = np.random.choice(range(1,100), 60)
	gammas = np.random.choice(range(1,50), 60)
	# vecinos = np.random.choice(range(1,tSet/K), 60)
	vecinos = [4,1000]
	gammas[0] = 15
	gammas[1] = 15
	alphas[0] = 20
	alphas[1] = 20
	hitsPCA = []
	hitsPLS = []
	for i in range(0,2):
		print '--Eleccion: ' + str(i) + '--'
		print 'Vecinos: ' + str(vecinos[i])
		print 'Alpha: ' + str(alphas[i])
		print 'Gamma: ' + str(gammas[i])
		print 'Fold: ' + str(K)
		header = '../data/' + ' ' + str(vecinos[i]) + ' ' + str(alphas[i]) + ' ' + str(gammas[i]) + ' ' +str(K)
		ffile = 'fold' + str(K) + '.in'
		kFold(header, tSet, K,'tests/'+ffile,seed)
		
		args = ["./tp", ffile, "c", "b"]
		popen = subprocess.Popen(args,stdout=subprocess.PIPE, stderr=subprocess.PIPE)
		out = popen.communicate()
		grafico(i, K, alphas[i], gammas[i], vecinos[i],ffile)
		hitsPCA.append(hitratePCA('tests/' + ffile + '_hit_rates',K,'i'+str(i)+'v'+str(vecinos[i])+'a'+str(alphas[i])+'f'+str(K)))
		hitsPLS.append(hitratePLS('tests/' + ffile + '_hit_rates',K,'i'+str(i)+'v'+str(vecinos[i])+'g'+str(gammas[i])+'f'+str(K)))
	hitsPCA.sort(key=operator.itemgetter(1))
	with open('tests/paramTest/PCA', 'w') as f:
	    for i in hitsPCA:
			f.write(str(i) + '\n')
		
	hitsPLS.sort(key=operator.itemgetter(1))
	with open('tests/paramTest/PLS', 'w') as f:
	    for j in hitsPLS:
			f.write(str(j) + '\n')
	return

tSet = 42000
seed= 0

paramTest(10,tSet,seed)
