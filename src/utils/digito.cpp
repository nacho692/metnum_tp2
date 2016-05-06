#include "digito.h"

Digito::Digito(const Digito& otro){
	(*this) = otro;
}


Digito::Digito(string clase, const vector<double>& vec){
	this->vec = vec;
	this->clase = clase;
	this->dim = vec.size();
}


double Digito::Norma() const{
	double sumCuadrados = 0;
	for(unsigned int i = 0; i < vec.size(); i++){
		sumCuadrados += (vec[i]*vec[i]);
	}

	return sqrt(sumCuadrados);
}
double Digito::DistanciaCuad(const Digito& otro) const{
	double sumCuadrados = 0;
	for(unsigned int i = 0; i < this->Dimension(); i++){
		double resta = otro[i] - (*this)[i];
		sumCuadrados += resta*resta;
	}
	return sumCuadrados;
}

unsigned int Digito::Dimension() const{
	return this->dim;
}

string Digito::Clase() const{
	return this->clase;
}


double& Digito::operator[](unsigned int i){
	return this->vec[i];
}

const double& Digito::operator[](unsigned int i) const{
	return this->vec[i];
}

Digito& Digito::operator=(const Digito& otro){
	vec = vector<double>(otro.vec);
	dim = otro.dim;
	clase = otro.clase;
	return *this;
}