#ifndef VECdoubleOR_H_
#define VECdoubleOR_H_

#include <vector>
#include <cmath>

using namespace std;


class Vector{
	private:
		vector<double> v;

	public:
		Vector();
		Vector(unsigned int n);
		Vector(const Vector& v2);
		unsigned int Dimension() const;
		void Agregar(const double& d);
		double SumaTotal() const;
		double Media() const;
		double Norma() const;
		double DistanciaCuad(const Vector& v2);
		Vector operator+(const Vector& v2) const;
		double operator*(const Vector& v2) const;//Asumo que el vector 
		Vector& operator=(const Vector& v2);
		const double& operator[](unsigned int i) const;
		double& operator[](unsigned int i);
};



#endif
