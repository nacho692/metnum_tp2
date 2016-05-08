#ifndef IDENTIFICADOR_H_
#define IDENTIFICADOR_H_
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include "../utils/matriz.h"

class Identificador{
	private:
		unsigned int alpha;
		unsigned int cantidad_vecinos;
		unsigned int gamma;
		
		Matriz tSet;
		vector<int> clases;

		Matriz Vt;

		struct Vecino{
			double distancia;
			int clase;
		};

		static bool cmpVecinoDistancia(const Vecino& v1,const Vecino& v2){
			return v1.distancia > v2.distancia;
		}

		static bool cmpVecinoClase(const Vecino& v1,const Vecino& v2){
			return v1.clase > v2.clase;
		}
		static bool dEq(double d1, double d2 = 0, double e = 0.0000001){
			return abs(d1-d2) < e;
		}

		//Tienen que modificar tSet y Vt ambas
		void PCA(const Matriz& set, unsigned int alpha);
		void PLS_DA(const Matriz& set, unsigned int gammma);
		void CentrarDividir(const Matriz& set, Matriz& X, Matriz& Xt) const;
	public:
		int kNN(const Vector& v) const;
		const Matriz& trainingSet() const;
		const Matriz& cambioBase() const;
};

#endif