#ifndef KNN_H_
#define KNN_H_

#include "digito.h"
#include "matriz.h"
#include <algorithm>
#include <vector>

using namespace std;
class kNN{
	private:
		unsigned int k;
		vector<Digito> set;
		void matrizMuestra(Matriz& set) const;
		double media(const vector<double>& v) const;

		struct Vecino{
			double distancia;
			string clase;
		};
		static bool cmpVecino(const Vecino& v1,const Vecino& v2){
			return v1.distancia > v2.distancia;
		}

	public:
		kNN(const unsigned int k);
		kNN(const unsigned int k,const vector<Digito>& trainingSet);
		void Agregar(const Digito& dig);
		string Identificar(const Digito& dig) const;

};
#endif //KNN_H_