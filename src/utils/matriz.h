#ifndef MATRIZ_H_
#define MATRIZ_H_

#include "vector.h"
#include <vector>
#include "../modulos/digito.h"

using namespace std;


class Matriz{
	private:
		vector<Vector> m;
		unsigned int ancho;
		unsigned int alto;
	public:
		Matriz();
		Matriz(unsigned int ancho, unsigned int alto);
		Matriz(const Matriz& otra);
		Matriz(const vector<Digito>& set);
		unsigned int Ancho() const;
		unsigned int Alto() const;
		void Transponer();
		double MetodoPotencia(Vector& x, unsigned int nit, Vector& v) const;

		Vector& operator[](unsigned int i);
		const Vector& operator[](unsigned int i) const;
		Matriz operator* (const Matriz& B) const;
		Matriz operator* (const double& b) const;
		Vector operator* (const Vector& v) const;
		Matriz operator+(const Matriz& B) const;
		Matriz& operator=(const Matriz& B);

		friend ostream& operator<<(ostream& os, const Matriz& B);
};

Matriz operator*(double b, const Matriz& B);


#endif
