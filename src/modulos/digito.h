#ifndef DIGITO_H_
#define DIGITO_H_

#include "../utils/vector.h"
#include <string>
#include <cmath>

using namespace std;

class Digito{
	private:
		Vector vec;
		string clase;

	public:
		Digito(string clase, const vector<double>& vec);
		Digito(const Digito& otro);
		unsigned int Dimension() const;
		double Norma() const;
		double Media() const;

		void Sumar(double s);
		void Escalar(double c);

		double DistanciaCuad(const Digito& otro) const;
		const string& Clase() const;

		double& operator[](unsigned int i);
		const double& operator[](unsigned int i) const;
		Digito& operator= (const Digito& otro);
};

#endif //DIGITO_H_