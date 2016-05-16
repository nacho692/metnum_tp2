#ifndef IDENTIFICADOR_H_
#define IDENTIFICADOR_H_
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include "../utils/matriz.h"

class Identificador{
	private:
		//unsigned int cantidad_vecinos;
		//unsigned int alpha;
		//unsigned int gamma;
		Matriz tSet;
		vector<int> clases;
		Vector medias;

		//Matriz cambio de base
		Matriz Vt;
		Vector autovalores;

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

		
		Vector CentrarDividir(Matriz& X) const;
		Matriz VectorMatriz(const Vector& t, const Matriz& X) const;
	public:
		Identificador( vector<int> clases);

		//Tienen que modificar tSet y Vt ambas
		void PCA(const Matriz& set, unsigned int alpha);
		void PLS_DA(const Matriz& set, unsigned int gamma);
		void SinMetodo(const Matriz& set);

		int kNN(const Vector& v,unsigned int kVecinos) const;
		//Getters
		const Matriz& trainingSet() const;
		const Matriz& cambioBase() const;
		const vector<int>& Clases()const;
		const Vector& AutoValores() const;
		//unsigned int Alpha()const;
		//unsigned int Gamma()const;
		unsigned int Cantidad_Vecinos()const;
};

#endif