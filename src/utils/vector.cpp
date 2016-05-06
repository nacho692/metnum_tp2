#include "vector.h"

Vector::Vector(){
}


Vector::Vector(unsigned int n){
	v = vector<double>(n);
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


double Vector::operator*(const Vector& v2) const{
	double t = 0;
	for (unsigned int i = 0; i < this->Dimension() ; i++ ){
		for (unsigned int j = 0; i < v2.Dimension() ; j++ ){
			t = t + v[i]*v[j];
		}
	}
	return t;
}


const double& Vector::operator[](unsigned int i) const{
	return v[i];
}


double& Vector::operator[](unsigned int i){
	return v[i];
}