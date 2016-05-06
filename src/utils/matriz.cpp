#include "matriz.h"


Matriz operator*(double b, const Matriz& B){
	return B*b;
}


Matriz::Matriz(unsigned int ancho, unsigned int alto){
	this->ancho = ancho;
	this->alto = alto;
	Vector v = Vector(ancho);
	m = vector< Vector >(ancho, v);
}

Matriz::Matriz(const vector<Digito>& set){
	for(unsigned int i = 0; i < set.size(); i++){
		vector<double> f;
		for(unsigned int j = 0; j < set[i].Dimension(); j++){
			f.push_back(set[i][j]);
		}
		m.push_back(f);
	}
}

Matriz::Matriz(const Matriz& otra){
	m = vector<Vector>(otra.m);
	this->ancho = otra.ancho;
	this->alto = otra.alto;
}

unsigned int Matriz::Ancho() const{
	return ancho;
}

unsigned int Matriz::Alto() const{
	return alto;
}

Matriz Matriz::operator+(const Matriz& B) const{
	Matriz A = (*this);
	for(unsigned int i = 0; i < this->Alto(); i++){
		for(unsigned int j = 0; j < this->Ancho(); j++){
			A[i][j] = m[i][j] + B[i][j];
		}
	}
	return A;
}

Matriz Matriz::operator*(const double& b) const{
	Matriz A = (*this);
	for(unsigned int i = 0; i < this->Alto(); i++){
		for(unsigned j = 0; j < this->Ancho(); j++){
			A[i][j] *= b;
		}
	}
	return A;
}

Matriz Matriz::operator*(const Matriz& B) const{
	//A = THIS*B
	Matriz C = B;
	C.Transponer();
	Matriz A(alto,B.Ancho());
	for(unsigned int i = 0; i < A.Alto(); i++){
		for(unsigned j = 0; j < A.Ancho(); j++){
			A[i][j] = m[i]*C[j];
		}
	}
	return A;
}

void Matriz::Transponer(){
	Matriz B(alto,ancho);
	for(unsigned int i = 0; i < this->Alto(); i++){
		for(unsigned j = 0; j < this->Ancho(); j++){
			B[j][i] = m[i][j];
		}
	}
	(*this) = B;
}



Vector& Matriz::operator[](unsigned int i){
	return m[i];
}

const Vector& Matriz::operator[](unsigned int i) const{
	return m[i];
}