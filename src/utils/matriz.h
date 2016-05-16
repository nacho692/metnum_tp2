#ifndef MATRIZ_H_
#define MATRIZ_H_

#include "vector.h"
#include <vector>
//#include "../modulos/digito.h"

using namespace std;


class Matriz{
	private:
		vector<Vector> m;
		unsigned int ancho;
		unsigned int alto;
		bool identidad = false;
	public:
		Matriz();
		Matriz(unsigned int ancho, unsigned int alto);
		Matriz(const Matriz& otra);
		Matriz(const Vector& v1, const Vector& v2);
		//Matriz(const vector<Digito>& set);
		unsigned int Ancho() const;
		unsigned int Alto() const;
		Matriz Transponer() const;
		double MetodoPotenciaNIteraciones(Vector& x, unsigned int nit) const;
		double MetodoPotenciaEpsilon(Vector& x, double e,unsigned int iter) const;
		bool Identidad() const;
		void Identidad(bool id);

		Vector& operator[](unsigned int i);
		const Vector& operator[](unsigned int i) const;
		Matriz operator* (const Matriz& B) const;
		Matriz operator* (const double& b) const;
		Vector operator* (const Vector& v) const;
		Matriz operator+(const Matriz& B) const;
		Matriz operator-(const Matriz& B) const;

		Matriz& operator=(const Matriz& B);

		friend ostream& operator<<(ostream& os, const Matriz& B);
};

Matriz operator*(double b, const Matriz& B);
Vector operator*(const Vector& v, const Matriz& B);

#endif
