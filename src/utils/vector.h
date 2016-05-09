#ifndef VECTOR_H_
#define VECTOR_H_

#include <vector>
#include <cmath>
#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


using namespace std;


class Vector{
	private:
		vector<double> v;

	public:
		Vector();
		Vector(unsigned int n);
		Vector(const Vector& v2);
		void RandomVector();
		unsigned int Dimension() const;
		void Agregar(const double& d);
		double SumaTotal() const;
		double Media() const;
		double Norma() const;
		void Resize(unsigned int n);
		double Distancia(const Vector& v2) const;
		Vector operator+(const Vector& v2) const;
		Vector operator-(const Vector& v2) const;
		double operator*(const Vector& v2) const;
		Vector operator*(const double& d) const;
		Vector& operator=(const Vector& v2);
		const double& operator[](unsigned int i) const;
		double& operator[](unsigned int i);

		friend ostream& operator<<(ostream& os, const Vector& vec);
};

Vector operator*(double d, const Vector& A);

#endif
