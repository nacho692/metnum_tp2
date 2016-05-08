#include "vector.h"

Vector operator*(double d, const Vector& A){
	return A*d;
}

Vector::Vector(){
}


Vector::Vector(unsigned int n){
	v = vector<double>(n);
}

Vector::Vector(const Vector& v2){
	*this = v2;
}


Vector::RandomVector(unsigned int length){
	Vector _randomVector = Vector(length);

	for(int i = 0; i < _randomVector.Dimension(); i++){
		// initialize random seed: 
  		srand (time(NULL));
		_randomVector[i] = srand();
	}

	Vector(_randomVector);
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

double Vector::Distancia(const Vector& v2) const{
	double sumCuadrados = 0;
	for(unsigned int i = 0; i < this->Dimension(); i++){
		double resta = v2[i] - (*this)[i];
		sumCuadrados += resta*resta;
	}
	return sqrt(sumCuadrados);
}


Vector Vector::operator+(const Vector& v2) const{
	Vector ret;
	ret = Vector(this->Dimension());
	for(unsigned int i = 0; i < this->Dimension() ; i++){
		ret[i] = (*this)[i]+v2[i];	
	}	
	return ret;
}

Vector Vector::operator-(const Vector& v2) const{
	Vector ret;
	ret = Vector(this->Dimension());
	for(unsigned int i = 0; i < this->Dimension() ; i++){
		ret[i] = (*this)[i]-v2[i];	
	}	
	return ret;
}

double Vector::operator*(const Vector& v2) const{
	double t = 0;
	for (unsigned int i = 0; i < this->Dimension() ; i++ ){
		t = t + v[i]*v2[i];
	}
	return t;
}

Vector Vector::operator*(const double& d) const{
	Vector v1 = Vector(this->Dimension());
	for (unsigned int i = 0; i < this->Dimension() ; i++ ){
		v1[i] = (*this)[i]*d;
	}
	return v1;
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

ostream& operator<<(ostream& os, const Vector& vec){
	os << "[ ";
	if(vec.Dimension() != 0 ){
	    for( unsigned int i = 0 ; i < vec.Dimension()-1 ; i++){
	    	os << vec[i] << ", ";
	    }
	    os << vec[vec.Dimension()-1];
	}
	os << ']';
    return os;
}