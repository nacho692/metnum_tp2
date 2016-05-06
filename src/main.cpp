#include <iostream>
#include <vector>
#include "utils/digito.h"
#include "utils/knn.h"

using namespace std;


int main(){
	vector<double> v1;
	v1.push_back(1);
	v1.push_back(1);
	vector<double> v2;
	v2.push_back(2);
	v2.push_back(1);
	vector<double> v3;
	v3.push_back(3);
	v3.push_back(1);
	vector<double> v4;
	v4.push_back(4);
	v4.push_back(1);

	vector<Digito> d;
	d.push_back(Digito("uno",v1));
	d.push_back(Digito("dos",v2));
	d.push_back(Digito("tres",v3));
	d.push_back(Digito("cuatro",v4));
	kNN k = kNN(3,d);

	vector<double> v5;
	v5.push_back(3);
	v5.push_back(4);

	Digito punto = Digito("",v5);
	cout << k.Identificar(punto) << endl;
	return 0;
}