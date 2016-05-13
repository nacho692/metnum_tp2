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
		string input_file_path;
		string output_file_path;			// el que va para kaggle
		string confusion_file_path;			// el de la matriz de confusion
		string hit_rates_file_path; 		// el de los hit rates
		string ciclos_de_clock_file_path; 	// el de los ciclos
		string autovalores_file_path;		// el de los autovectores
		string recall_file_path;
		string precision_file_path;
		string f1_file_path;

		unsigned int cantidad_vecinos;
		unsigned int alpha;
		unsigned int gamma;
		unsigned int cantidad_folds;

		vector< vector< unsigned int > > folds; // vector de 1 y 0 que me dice si el i-esimo valor es de training (1) o si es de testing (1) para el j-esimo fold
		Matriz digitos;
		vector<int> labels;

		Matriz digitos_testing;
		vector<int> labels_testing;

		Matriz digitos_training;
		vector<int> labels_training;

	public:
		LevantaDatos(string input_file_name,string output_file_name);
		void SetearKesimoFold(unsigned int k);
		void EscribirResultados(const int clocks_para_seteo_cambio_base, const int clocks_para_reconocimiento, const Matriz& matriz_confusion, const double& hit_rate, const Vector& autovalores, const Vector& precision, const Vector& recall);

		string FilePath() const;
		unsigned int CantidadVecinos() const;
		unsigned int Alpha() const;
		unsigned int Gamma() const;
		unsigned int CantidadFolds() const;

		const Matriz& MatrizTraining() const;
		const vector<int>& LabelsTraining() const;

		const Matriz& MatrizTesting() const;
		const vector<int>& LabelsTesting() const;
};

#endif