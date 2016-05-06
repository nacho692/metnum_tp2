#ifndef VECdoubleOR_H_
#define VECdoubleOR_H_

#include <vector>

using namespace std;


class Vector{
	private:
		vector<double> v;

	public:
		Vector();
		Vector(unsigned int n);
		unsigned int Dimension() const;
		void Agregar(const double& d);
		double SumaTotal() const;
		double Media() const;
		//Norma();
		//Suma();
		//Distancia();
		double operator*(const Vector& v2) const;//Asumo que el vector 

		const double& operator[](unsigned int i) const;
		double& operator[](unsigned int i);
};



#endif
