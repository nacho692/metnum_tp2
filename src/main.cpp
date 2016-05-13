#include "modulos/identificador.h"
#include "modulos/escupe_datos.h"
#include "modulos/levanta_datos.h"
#include <chrono>
#include <ctime>

using namespace std::chrono;
using namespace std;

void imprmirVectorInt(Vector& v){
	cout << "[";

	for (int i = 0; i < v.Dimension()-1; i++){
		cout << v[i] << ", ";
	}

	cout << v[v.Dimension()-1] << "]" << endl;
}

void testearTrainingSet(Identificador& id, LevantaDatos& ld, Matriz& matriz_confusion, double& hit_rate, clock_t& clocks_para_fold, Vector& precision, Vector& recall){
	Vector cantidades(10);
	double cantidad = 0;

	Vector verdaderos_positivos(10);
	Vector falsos_positivos(10);
	Vector falsos_negativos(10);

	for(unsigned int i = 0; i < ld.LabelsTesting().size(); i++){
		int label =  ld.LabelsTesting()[i];
		cantidades[label] ++;
		cantidad++;

		clock_t begin_reconocimiento = clock();
		int res = id.kNN(ld.MatrizTesting()[i],ld.CantidadVecinos());
		clock_t end_reconocimiento = clock();
		clocks_para_fold = clocks_para_fold + end_reconocimiento - begin_reconocimiento;
		
		matriz_confusion[label][res]++;
		if (res == label){
			hit_rate++;
			verdaderos_positivos[label]++;
		} else {
			falsos_positivos[res]++;
			falsos_negativos[label]++;
		}

	}


	hit_rate = hit_rate / cantidad;

	for (int i = 0; i < 10; ++i){
		precision[i] = verdaderos_positivos[i] / (verdaderos_positivos[i] + falsos_positivos[i]);
		recall[i] = verdaderos_positivos[i] / (verdaderos_positivos[i] + falsos_negativos[i]);
	}
}

void testearKesimoFold(int fold, LevantaDatos& ld, int metodo){
	// metodo 0 = PCA
	// metodo 1 = PLS
	
	if (metodo) cout << "\tPreparando identificador para PLS-DA con los folds de training..." << endl;
	else cout << "\tPreparando identificador para PCA con los folds de training..." << endl;

	Matriz mt = ld.MatrizTraining();
	Identificador id(ld.LabelsTraining());

	clock_t begin_seteo = clock();
	if (metodo){
		id.PLS_DA(mt, ld.Gamma());
	} else {
		id.PCA(mt, ld.Alpha());
	}
	clock_t end_seteo = clock();

	const int clocks_para_seteo_cambio_base = int (end_seteo - begin_seteo);

	cout << "\tReconociendo dígitos del fold de testing..." << endl;
	clock_t clocks_para_reconocimiento_temp = 0;
	Matriz matriz_confusion(10, 10);
	double hit_rate = 0;
	Vector precision(10);
	Vector recall(10);
	testearTrainingSet(id, ld, matriz_confusion, hit_rate, clocks_para_reconocimiento_temp, precision, recall);
	const int clocks_para_reconocimiento = (const int) clocks_para_reconocimiento_temp;

	ld.EscribirResultados(clocks_para_seteo_cambio_base, clocks_para_reconocimiento, matriz_confusion, hit_rate, id.AutoValores(), precision, recall);
}

void testAlphaPCA(unsigned int fold, LevantaDatos& ld, unsigned int iter, unsigned int subSet){
	cout << "Seteando " << fold << "-esimo fold..." << endl;
	ld.SetearKesimoFold(fold);
	Matriz mt(ld.MatrizTraining().Ancho(), subSet);
	for(unsigned int i; i < subSet; i++){
		mt[i] = ld.MatrizTraining()[i];
	}

	cout << "Tamaño training set: " << mt.Alto() << endl;

	Identificador id(ld.LabelsTraining());
	
	cout << "Alpha: " << 1 << endl;
	for(unsigned int j = 0; j < iter; j++){
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		id.PCA(mt,1);
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		cout << duration_cast<microseconds>( t2 - t1 ).count()/1000 << ", "<<flush;
	}
	cout << endl;
	for(unsigned int i = 56; i <= 784; i+=56 ){
		cout << "Alpha: " << i << endl;
		for(unsigned int j = 0; j < iter; j++){
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			id.PCA(mt,i);
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			cout << duration_cast<microseconds>( t2 - t1 ).count()/1000 << ", "<< flush;
		}
		cout << endl;
	}

}

void testGammaPLS(unsigned int fold, LevantaDatos& ld, unsigned int iter, unsigned int subSet){
	cout << "Seteando " << fold << "-esimo fold..." << endl;
	ld.SetearKesimoFold(fold);
	
	Matriz mt(ld.MatrizTraining().Ancho(), subSet);
	for(unsigned int i; i < subSet; i++){
		mt[i] = ld.MatrizTraining()[i];
	}

	cout << "Tamaño training set: " << mt.Alto() << endl;

	Identificador id(ld.LabelsTraining());
	
	cout << "Gamma	: " << 1 << endl;
	for(unsigned int j = 0; j < iter; j++){
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		id.PLS_DA(mt,1);
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		cout << duration_cast<microseconds>( t2 - t1 ).count()/1000 << ", "<<flush;
	}
	cout << endl;
	for(unsigned int i = 56; i <= 784; i+=56 ){
		cout << "Gamma: " << i << endl;
		for(unsigned int j = 0; j < iter; j++){
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			id.PLS_DA(mt,i);
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			cout << duration_cast<microseconds>( t2 - t1 ).count()/1000 << ", "<< flush;
		}
		cout << endl;
	}

}

void testVecinosPCA(unsigned int fold, LevantaDatos& ld, unsigned int iter, unsigned int subSet){
		cout << "Seteando " << fold << "-esimo fold..." << endl;
	ld.SetearKesimoFold(fold);
	
	Matriz mt(ld.MatrizTraining().Ancho(), subSet);
	for(unsigned int i; i < subSet; i++){
		mt[i] = ld.MatrizTraining()[i];
	}

	cout << "Tamaño training set: " << mt.Alto() << endl;

	Identificador id(ld.LabelsTraining());
	
	id.PCA(mt,50);
	cout << "Setup Completo" << endl;

	for(unsigned int i = 1; i <= mt.Alto(); i+= 50){
		cout << "Vecinos: " << i << endl;
		for(unsigned int j = 0; j < iter; j++){
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			id.kNN(ld.MatrizTesting()[0],i);
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			cout << duration_cast<microseconds>( t2 - t1 ).count()/1000 << ", "<< flush;
		}
		cout << endl;
	}
}


void testVecinosPLS(unsigned int fold, LevantaDatos& ld, unsigned int iter, unsigned int subSet){
	cout << "Seteando " << fold << "-esimo fold..." << endl;
	ld.SetearKesimoFold(fold);
	
	Matriz mt(ld.MatrizTraining().Ancho(), subSet);
	for(unsigned int i; i < subSet; i++){
		mt[i] = ld.MatrizTraining()[i];
	}

	cout << "Tamaño training set: " << mt.Alto() << endl;

	Identificador id(ld.LabelsTraining());
	
	id.PLS_DA(mt,50);
	cout << "Setup Completo" << endl;

	for(unsigned int i = 1; i <= mt.Alto(); i+= 50){
		cout << "Vecinos: " << i << endl;
		for(unsigned int j = 0; j < iter; j++){
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			id.kNN(ld.MatrizTesting()[0],i);
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			cout << duration_cast<microseconds>( t2 - t1 ).count()/1000 << ", "<< flush;
		}
		cout << endl;
	}
}

void testVecinosSinMetodo(unsigned int fold, LevantaDatos& ld, unsigned int iter, unsigned int subSet){
	cout << "Seteando " << fold << "-esimo fold..." << endl;
	ld.SetearKesimoFold(fold);
	
	Matriz mt(ld.MatrizTraining().Ancho(), subSet);
	for(unsigned int i; i < subSet; i++){
		mt[i] = ld.MatrizTraining()[i];
	}

	cout << "Tamaño training set: " << mt.Alto() << endl;

	Identificador id(ld.LabelsTraining());
	
	id.SinMetodo(mt);
	cout << "Setup Completo" << endl;

	for(unsigned int i = 1; i <= mt.Alto(); i+= 50){
		cout << "Vecinos: " << i << endl;
		for(unsigned int j = 0; j < iter; j++){
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			id.kNN(ld.MatrizTesting()[0],i);
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			cout << duration_cast<microseconds>( t2 - t1 ).count()/1000 << ", "<< flush;
		}
		cout << endl;
	}
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
	//LevantaDatos ld(nombre_entrada, nombre_salida);
	//testGammaPLS(0,ld,10,20000);
	//testAlphaPCA(0,ld,10,20000);
	//testVecinosPLS(0,ld,10,20000);
	//testVecinosPCA(0,ld,10,20000);
	//testVecinosSinMetodo(0,ld,10,20000);
	//testear(1, ld);
	//cout << endl;

	LevantaDatos ld(nombre_entrada, nombre_salida);

	cout << "    Cantidad vecinos : " << ld.CantidadVecinos() << endl;
	cout << "    Alpha : " << ld.Alpha() << endl;
	cout << "    Gamma : " << ld.Gamma() << endl;
	cout << "    Cantidad fold : " << ld.CantidadFolds() << endl;

/*	ld.SetearKesimoFold(1);
	testearKesimoFold(1, ld, 0);
*/
	for (int i = 0; i < ld.CantidadFolds(); i++){
	 	cout << "Seteando " << i << "-esimo fold..." << endl;
	 	ld.SetearKesimoFold(i);
	 	cout << "Testeando con PCA..." << endl;
	 	//testearKesimoFold(i, ld, 0);
	 	cout << "Testeando con PLS-DA..." << endl;
		testearKesimoFold(i, ld, 1);
	}

	return 0;
}
