#include "matriz.h"


Matriz operator*(double b, const Matriz& B){
	return B*b;
}

Vector operator*(const Vector& v, const Matriz& B){
	return B.Transponer()*v;
}


Matriz::Matriz(){
	this->identidad = false;
}
Matriz::Matriz(const Vector& v1, const Vector& v2){
	(*this) = Matriz(v2.Dimension(),v1.Dimension());

	for(unsigned int i = 0; i < v1.Dimension(); i++){
		for(unsigned int j = 0; j < v2.Dimension(); j++){
			m[i][j] = v1[i]*v2[j];
		}
	}
	this->identidad = false;
}

Matriz::Matriz(unsigned int ancho, unsigned int alto){
	this->identidad = false;
	this->ancho = ancho;
	this->alto = alto;
	Vector v = Vector(ancho);
	m = vector< Vector >(alto, v);
}
bool Matriz::Identidad()const{
	return this->identidad;
}
void Matriz::Identidad(bool id){
	this->identidad = id;
}

Matriz::Matriz(const Matriz& otra){
	m = vector<Vector>(otra.m);
	this->ancho = otra.ancho;
	this->alto = otra.alto;
	this->identidad = otra.identidad;
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

Matriz Matriz::operator-(const Matriz& B) const{
	Matriz A = (*this);
	for(unsigned int i = 0; i < this->Alto(); i++){
		for(unsigned int j = 0; j < this->Ancho(); j++){
			A[i][j] = m[i][j] - B[i][j];
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
	Matriz C = B.Transponer();
	Matriz A(B.Ancho(),alto);
	for(unsigned int i = 0; i < A.Alto(); i++){
		for(unsigned j = 0; j < A.Ancho(); j++){
			A[i][j] = m[i]*C[j];
		}
	}
	return A;
}

//Multiplica un B*v
Vector Matriz::operator*(const Vector& v) const{
	Vector v2 = Vector(Alto());

	for (unsigned int i = 0 ; i < this->Alto(); i++ ){
		v2[i] = this->m[i]*v;
	}
	return v2;
}

Matriz Matriz::Transponer() const{
	Matriz B(alto,ancho);
	for(unsigned int i = 0; i < this->Alto(); i++){
		for(unsigned j = 0; j < this->Ancho(); j++){
			B[j][i] = m[i][j];
		}
	}
	return B;
}

double Matriz::MetodoPotenciaNIteraciones(Vector& x, unsigned int nit) const{
	double a;
	Matriz B = Matriz(*this);
	for (unsigned int i = 1 ; i <= nit ; i++ ){
		x = B*x;
		x = x*(1/(x.Norma()));
	}
	a = (x*(B*x)) / (x*x);
	return a;
}

double Matriz::MetodoPotenciaEpsilon(Vector& x, double e, unsigned int iter) const{
	double a;
	Matriz B = Matriz(*this);
	Vector xNuevo = (B*x);
	xNuevo = xNuevo * (1/xNuevo.Norma());
	for (unsigned int i = 1 ; x.Distancia(xNuevo) > e && i < iter; i++ ){
		x = xNuevo;
		xNuevo = B*x;
		xNuevo = xNuevo*(1/((xNuevo).Norma()));
	}
	a = (xNuevo*(B*xNuevo)) / (xNuevo*xNuevo);
	x = xNuevo;
	return a;
}


Vector& Matriz::operator[](unsigned int i){
	return m[i];
}

const Vector& Matriz::operator[](unsigned int i) const{
	return m[i];
}

Matriz& Matriz::operator=(const Matriz& B){
	m = B.m;
	ancho = B.ancho;
	alto = B.alto;
	return *this;
}

ostream& operator<<(ostream& os, const Matriz& B){
	os << endl;
	if( B.Alto() == 0 || B.Ancho() == 0 ){
		os << "[ ]";
	}else{
		for( unsigned int i = 0 ; i < B.Alto() ; i++){
			os << B[i];
			os << endl;
		}
	}
	return os;
}