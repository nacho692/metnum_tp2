#ifndef IDENTIFICADOR_H_
#define IDENTIFICADOR_H_
#include <vector>
#include <algorithm>
#include <string>
#include "../utils/matriz.h"

class Identificador{
	private:
		unsigned int alpha;
		unsigned int kVecinos;
		unsigned int gamma;
		
		Matriz tSet;
		vector<string> clases;

		Matriz Vt;

		struct Vecino{
			double distancia;
			string clase;
		};

		static bool cmpVecinoDistancia(const Vecino& v1,const Vecino& v2){
			return v1.distancia > v2.distancia;
		}

		static bool cmpVecinoClase(const Vecino& v1,const Vecino& v2){
			return v1.clase > v2.clase;
		}

		//Tienen que modificar tSet y Vt ambas
		void PCA(const Matriz& set, unsigned int alpha);
		void PLS_DA(const Matriz& set, unsigned int gammma);

	public:
		string kNN(const Vector& v) const;
		const Matriz& trainingSet() const;
		const Matriz& cambioBase() const;
};

#endif