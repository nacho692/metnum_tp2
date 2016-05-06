#ifndef VECTOR_H_
#define VECTOR_H_

#include <vector>

using namespace std;

template<typename T>
class Vector{
	private:
		vector<T> v;

	public:
		Vector();
		Vector(unsigned int n);
		unsigned int Dimension() const;
		void Agregar(const T& d);
		T SumaTotal() const;
		double Media() const;
		//Norma();
		//Suma();
		//Distancia();
		T operator*(const Vector<T>& v2) const;//Asumo que el vector 

		const T& operator[](unsigned int i) const;
		T& operator[](unsigned int i);
};

template<typename T>
Vector<T>::Vector(){
}

template<typename T>
Vector<T>::Vector(unsigned int n){
	v = vector<T>(n);
}

template<typename T>
unsigned int Vector<T>::Dimension() const{
	return v.size();
}

template<typename T>
void Vector<T>::Agregar(const T& d){
	v.push_back(d);
}

template<typename T>
T Vector<T>::SumaTotal() const{
	T t = T();
	for (unsigned int i = 0; i < this->Dimension() ; i++ ){
		t = t + v[i];
	}
	return t;
}

template<typename T>
double Vector<T>::Media() const{
	return (double) this->SumaTotal()/this->Dimension();
}

template<typename T>
T Vector<T>::operator*(const Vector<T>& v2) const{
	T t = T();
	for (unsigned int i = 0; i < this->Dimension() ; i++ ){
		for (unsigned int j = 0; i < v2.Dimension() ; j++ ){
			t = t + v[i]*v[j];
		}
	}
	return t;
}

template<typename T>
const T& Vector<T>::operator[](unsigned int i) const{
	return v[i];
}

template<typename T>
T& Vector<T>::operator[](unsigned int i){
	return v[i];
}

#endif
