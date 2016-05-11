#include "modulos/identificador.h"
#include "modulos/escupe_datos.h"
#include "modulos/levanta_datos.h"

#include <ctime>

using namespace std;

void imprmirVectorInt(vector<double>& v){
	cout << "[";

	for (int i = 0; i < v.size()-1; i++){
		cout << v[i] << ", ";
	}

	cout << v[v.size()-1] << "]" << endl;
}

void testearTrainingSet(Identificador& id, LevantaDatos& ld, Matriz& matriz_confusion, vector<double>& hit_rates, clock_t& clocks_para_fold){
	vector<int> cantidades(10);
	for(unsigned int i = 0; i < ld.LabelsTesting().size(); i++){
		int label =  ld.LabelsTesting()[i];
		cantidades[label] ++;

		clock_t begin_reconocimiento = clock();
		int res = id.kNN(ld.MatrizTesting()[i]);
		clock_t end_reconocimiento = clock();

		clocks_para_fold = clocks_para_fold + end_reconocimiento - begin_reconocimiento;
		

		matriz_confusion[res][label]++;
		if (res == label){
			hit_rates[label]++;
		}
	}	

	for (int i = 0; i < 10; ++i)
	{
		hit_rates[i] = double(hit_rates[i]) / double(cantidades[i]);
	}
}

void testearKesimoFold(int fold, LevantaDatos& ld, int metodo){
	// metodo 0 = PCA
	// metodo 1 = PLS
	
	if (metodo) cout << "Preparando identificador para PLS-DA con los folds de training..." << endl;
	else cout << "Preparando identificador para PCA con los folds de training..." << endl;

	Matriz mt = ld.MatrizTraining();
	Identificador id(ld.LabelsTraining(),ld.CantidadVecinos());

	clock_t begin_seteo = clock();
	if (metodo) id.PCA(mt, ld.Alpha());
	else id.PLS_DA(mt, ld.Gamma());
	clock_t end_seteo = clock();

	int clocks_para_seteo_cambio_base = int (end_seteo - begin_seteo);

	cout << "\tReconociendo dígitos del fold de testing..." << endl;
	clock_t clocks_para_reconocimiento_temp = 0;
	Matriz matriz_confusion(10, 10);
	vector<double> hit_rates(10);
	testearTrainingSet(id, ld, matriz_confusion, hit_rates, clocks_para_reconocimiento_temp);
	int clocks_para_reconocimiento = (int) clocks_para_reconocimiento_temp;

	ld.EscribirResultados(clocks_para_seteo_cambio_base, clocks_para_reconocimiento, matriz_confusion, hit_rates);
}

int main(int argc, char const *argv[]){ 
	/* argv
	nombre_entrada
	nombre_salida
	metodo_a_utilizar	(0: kNN , 1: PCA + kNN ,2: PLS-DA + kNN)
	*/
	string nombre_entrada(argv[1]);
	string nombre_salida(argv[2]);		// En este voy a escribir los autovalores
	string metodo_a_utilizar(argv[3]);

	cout << "Levantando datos..." << endl;
	cout << endl;

	LevantaDatos ld(nombre_entrada, nombre_salida);

	for (int i = 0; i < ld.CantidadFolds(); i++){

		cout << "Seteando " << i << "-esimo fold..." << endl;
		cout << endl;
		ld.SetearKesimoFold(i);
		testearKesimoFold(i, ld, 0);
		cout << endl;
		testearKesimoFold(i, ld, 1);
		cout << endl;
	}

	return 0;
}