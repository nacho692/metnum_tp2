
#include "identificador.h"

const Matriz& Identificador::cambioBase() const{
	return Vt;
}

const Matriz& Identificador::trainingSet() const{
	return tSet;
}

string Identificador::kNN(const Vector& v) const{
	//TODO: Cambio de base con V

	vector<Vecino> distancias;
	for(unsigned int i = 0; i < tSet.Alto(); i++){
		Vecino d;
		d.distancia = v.Distancia(tSet[i]);
		d.clase = clases[i];
		distancias.push_back(d);
	}

	make_heap(distancias.begin(),distancias.end(),cmpVecinoDistancia);

	vector<Vecino> vecinos;
	for(unsigned int i = 0; i < kVecinos; i++){
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
