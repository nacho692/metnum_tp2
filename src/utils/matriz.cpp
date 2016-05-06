#include "matriz.h"

Matriz::Matriz(const vector<Digito>& set){
	for(unsigned int i = 0; i < set.size(); i++){
		vector<double> f;
		for(unsigned int j = 0; j < set[i].Dimension(); j++){
			f.push_back(set[i][j]);
		}
		m.push_back(f);
	}
}
unsigned int Matriz::Ancho() const{
	unsigned int ancho = 0;
	if (m.size() != 0){
		ancho = m[0].size();
	}
	return ancho;
}

unsigned int Matriz::Alto() const{
	return m.size();
}

void Matriz::Sumar(const Matriz& s){
	for(unsigned int i = 0; i < this->Alto(); i++){
		for(unsigned int j = 0; j < this->Ancho(); j++){
			(*this)[i][j] += s[i][j];
		}
	}
}

void Matriz::Multiplicar(double c){
	for(unsigned int i = 0; i < this->Alto(); i++){
		for(unsigned j = 0; j < this->Ancho(); j++){
			(*this)[i][j] *= c;
		}
	}
}


vector<double>& Matriz::operator[](unsigned int i){
	return m[i];
}

const vector<double>& Matriz::operator[](unsigned int i) const{
	return m[i];
}