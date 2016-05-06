#include "knn.h"

kNN::kNN(const unsigned int k){
	this->k = k;
}

kNN::kNN(const unsigned int k,const vector<Digito>& trainingSet){
	this->k = k;
	//set = trainingSet;
	Matriz X = Matriz(trainingSet);
	matrizMuestra(X);
}

void kNN::matrizMuestra(Matriz& X) const{
	unsigned int n = X.Ancho();
	double escalar = 1/(sqrt(n-1));
	for(unsigned int i = 0; i < X.Alto(); i++){
		double mu = media(X[i]);
	}
	X.Multiplicar(escalar);
}

//TODO: Cambiar por la media de vector
double kNN::media(const vector<double>& v) const{
	double suma = 0;
	for(unsigned int i = 0; i < v.size(); i++){
		suma += v[i];
	}
	return suma/v.size();
}


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

	make_heap(distancias.begin(),distancias.end(),cmpVecino);

	vector<Vecino> vecinos;
	for(unsigned int i = 0; i < k; i++){
		pop_heap(distancias.begin(), distancias.end(),cmpVecino);
		vecinos.push_back(distancias[distancias.size()-1]);
		distancias.pop_back();
	}
	return vecinos[0].clase;
}
