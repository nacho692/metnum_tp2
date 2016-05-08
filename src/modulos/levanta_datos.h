#ifndef LEVANTA_DATOS_H_
#define LEVANTA_DATOS_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "../utils/matriz.h"

using namespace std;

class LevantaDatos{
	private:
		string file_path;
		unsigned int cantidad_vecinos;
		unsigned int alpha;
		unsigned int gamma;
		unsigned int cantidad_folds;

		vector< vector< unsigned int > > folds; // vector de 1 y 0 que me dice si el i-esimo valor es de training (1) o si es de testing (1) para el j-esimo fold
		Matriz digitos;
		vector<string> labels;

		Matriz digitos_testing;
		vector<string> labels_testing;

		Matriz digitos_training;
		vector<string> labels_training;

	public:
		LevantaDatos();
		void SetearKesimoFold(unsigned int k);

		string FilePath() const;
		unsigned int CantidadVecinos() const;
		unsigned int Alpha() const;
		unsigned int Gamma() const;
		unsigned int CantidadFolds() const;

		const Matriz& MatrizTraining() const;
		const vector<string>& LabelsTraining() const;

		const Matriz& MatrizTesting() const;
		const vector<string>& LabelsTesting() const;
};

#endif