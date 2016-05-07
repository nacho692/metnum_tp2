#ifndef KNN_H_
#define KNN_H_

#include "digito.h"
#include "../utils/matriz.h"
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;
class kNN{
	private:
		unsigned int k;
		vector<Digito> set;
		//void matrizMuestra(Matriz& set) const;

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


	public:
		kNN(const unsigned int k);
		kNN(const unsigned int k,const vector<Digito>& trainingSet);
		void Agregar(const Digito& dig);
		string Identificar(const Digito& dig) const;

};
#endif //KNN_H_