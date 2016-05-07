#include "knn.h"

kNN::kNN(const unsigned int k){
	this->k = k;
}

kNN::kNN(const unsigned int k,const vector<Digito>& trainingSet){
	this->k = k;
	set = trainingSet;
	//Matriz X = Matriz(trainingSet);
	//matrizMuestra(X);
}
/*
void kNN::matrizMuestra(Matriz& X) const{
	unsigned int n = X.Ancho();
	double escalar = 1/(sqrt(n-1));
	for(unsigned int i = 0; i < X.Alto(); i++){
		double mu = X[i].Media();
		//TODO:Resta de vector
		for(unsigned int j = 0; j < X.Ancho(); j++){
			X[i][j] -= mu;
		}
	}
	X = X*escalar;
}*/

void kNN::Agregar(const Digito& dig){
	set.push_back(dig);
}


string kNN::Identificar(const Digito& dig) const{
	vector<Vecino> distancias;
	for(unsigned int i = 0; i < set.size(); i++){
		Vecino d;
		d.distancia = dig.DistanciaCuad(set[i]);
		d.clase = set[i].Clase();
		distancias.push_back(d);
	}

	make_heap(distancias.begin(),distancias.end(),cmpVecinoDistancia);

	vector<Vecino> vecinos;
	for(unsigned int i = 0; i < k; i++){
		pop_heap(distancias.begin(), distancias.end(),cmpVecinoDistancia);
		vecinos.push_back(distancias[distancias.size()-1]);
		distancias.pop_back();
	}

	//Por si ya lo teniamos cargado en el training set basicamente
	if(vecinos[0].distancia == 0){
		return vecinos[0].clase;
	}

	//Ordenamos para juntar cada clase y asi sacar el voto calificado mas facil (no tengo acentos)
	sort(vecinos.begin(),vecinos.end(),cmpVecinoClase);
	double max = 0;
	double sum = 0;
	string claseMax;
	string clase = vecinos[0].clase;
	for(unsigned int i = 0; i < vecinos.size(); i++){
		//Si llegue al final o si cambio de clase, me fijo si supera al maximo anterior
		if(clase != vecinos[i].clase || i == vecinos.size()-1){
			//Sumo el ultimo si es la ultima vuelta
			sum += (1/vecinos[i].distancia)*(i== vecinos.size()-1); 
			if(sum > max){
				max = sum;
				claseMax = clase;
			}
			sum = 0;
			clase = vecinos[i].clase;
		}
		sum += (1/vecinos[i].distancia);
	}

	return claseMax;
}
