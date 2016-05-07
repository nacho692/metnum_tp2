#include <iostream>
#include <vector>
#include "modulos/digito.h"
#include "modulos/knn.h"
#include "utils/vector.h"
#include "modulos/levanta_datos.h"

using namespace std;


int main(){
	Vector v1;
	v1.Agregar(1);
	v1.Agregar(1);
	Vector v2;
	v2.Agregar(2);
	v2.Agregar(1);
	Vector v3;
	v3.Agregar(3);
	v3.Agregar(1);
	Vector v4;
	v4.Agregar(4);
	v4.Agregar(1);

	vector<Digito> d;
	d.push_back(Digito("uno",v1));
	d.push_back(Digito("dos",v2));
	d.push_back(Digito("tres",v3));
	d.push_back(Digito("cuatro",v4));
	kNN k = kNN(3,d);

	Vector v5;
	v5.Agregar(3);
	v5.Agregar(4);

	Digito punto = Digito("",v5);
	cout << k.Identificar(punto) << endl;

	LevantaDatos lev = LevantaDatos();


	return 0;
}