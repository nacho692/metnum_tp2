#include "digito.h"

Digito::Digito(const Digito& otro){
	(*this) = otro;
}


Digito::Digito(string clase, const vector<double>& vec){
	this->vec = vec;
	this->clase = clase;
}


double Digito::Norma() const{
	return vec.Norma();
}
double Digito::DistanciaCuad(const Digito& otro) const{
	return vec.DistanciaCuad(otro.vec);
}

unsigned int Digito::Dimension() const{
	return vec.Dimension();
}

const string& Digito::Clase() const{
	return this->clase;
}


double& Digito::operator[](unsigned int i){
	return this->vec[i];
}

const double& Digito::operator[](unsigned int i) const{
	return this->vec[i];
}

Digito& Digito::operator=(const Digito& otro){
	vec = Vector(otro.vec);
	clase = otro.clase;
	return *this;
}