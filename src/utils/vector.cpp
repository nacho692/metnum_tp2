#include "vector.h"

Vector::Vector(){
}


Vector::Vector(unsigned int n){
	v = vector<double>(n);
}

Vector::Vector(const Vector& v2){
	*this = v2;
}

unsigned int Vector::Dimension() const{
	return v.size();
}


void Vector::Agregar(const double& d){
	v.push_back(d);
}


double Vector::SumaTotal() const{
	double t = double();
	for (unsigned int i = 0; i < this->Dimension() ; i++ ){
		t = t + v[i];
	}
	return t;
}


double Vector::Media() const{
	return this->SumaTotal()/this->Dimension();
}

double Vector::Norma() const{
	double sumCuadrados = 0;
	for(unsigned int i = 0; i < v.size(); i++){
		sumCuadrados += ((*this)[i]*(*this)[i]);
	}

	return sqrt(sumCuadrados);
}

double Vector::DistanciaCuad(const Vector& v2){
	double sumCuadrados = 0;
	for(unsigned int i = 0; i < this->Dimension(); i++){
		double resta = v2[i] - (*this)[i];
		sumCuadrados += resta*resta;
	}
	return sumCuadrados;
}


Vector Vector::operator+(const Vector& v2) const{
	Vector ret;
	ret = Vector(this->Dimension());
	for(unsigned int i = 0; i < this->Dimension() ; i++){
		ret[i] = (*this)[i]+v2[i];	
	}	
	return ret;
}

double Vector::operator*(const Vector& v2) const{
	double t = 0;
	for (unsigned int i = 0; i < this->Dimension() ; i++ ){
		for (unsigned int j = 0; i < v2.Dimension() ; j++ ){
			t = t + v[i]*v[j];
		}
	}
	return t;
}

Vector& Vector::operator=(const Vector& v2){
	v = v2.v;
	return *this;
}

const double& Vector::operator[](unsigned int i) const{
	return v[i];
}


double& Vector::operator[](unsigned int i){
	return v[i];
}