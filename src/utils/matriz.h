#ifndef MATRIZ_H_
#define MATRIZ_H_

#include <vector>
#include "digito.h"

using namespace std;

class Matriz{
	private:
		vector<vector <double> > m;

	public:
		Matriz();
		Matriz(const vector<Digito>& set);
		unsigned int Ancho() const;
		unsigned int Alto() const;
		void Sumar(const Matriz& s);
		void Multiplicar(double c);

		vector<double>& operator[](unsigned int i);
		const vector<double>& operator[](unsigned int i) const;
};

#endif
