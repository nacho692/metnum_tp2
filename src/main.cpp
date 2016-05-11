#include "modulos/identificador.h"
#include "modulos/escupe_datos.h"
#include "modulos/levanta_datos.h"
#include <chrono>



using namespace std::chrono;
using namespace std;

void testearTrainingSet(Identificador& id, LevantaDatos& ld, Matriz& matriz_confusion){
	// for(unsigned int i = 0; i < ld.LabelsTesting().size(); i++){
	for(unsigned int i = 0; i < ld.LabelsTesting().size(); i++){
		int label =  ld.LabelsTesting()[i];
		int res = id.kNN(ld.MatrizTesting()[i]);
		matriz_confusion[res][label]++;
	}	
}

void testear(int fold, LevantaDatos& ld){
	cout << "Seteando " << fold << "-esimo fold..." << endl;
	ld.SetearKesimoFold(fold);

	cout << "Preparando identificador para PCA con los folds de training..." << endl;
	Matriz mt = ld.MatrizTraining();
	Identificador id(ld.LabelsTraining(),ld.CantidadVecinos());
	id.PCA(mt,100);

	cout << "Reconociendo dígitos del fold de testing..." << endl;
	Matriz matriz_confusion(10, 10);
	testearTrainingSet(id, ld, matriz_confusion);

	cout << "Matriz de confusion : " << endl;
	cout << matriz_confusion << endl;
	// EscupeDatos ep(nombre_salida, matriz_confusion);
}

void testAlphaPCA(unsigned int fold, LevantaDatos& ld, unsigned int iter){
	cout << "Seteando " << fold << "-esimo fold..." << endl;
	ld.SetearKesimoFold(fold);
	Matriz mt = ld.MatrizTraining();
	cout << "Tamaño training set: " << mt.Alto() << endl;

	Identificador id(ld.LabelsTraining(),ld.CantidadVecinos());
	
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

int main(int argc, char const *argv[]){ 
	/* argv
	nombre_entrada
	nombre_salida
	metodo_a_utilizar	(0: kNN , 1: PCA + kNN ,2: PLS-DA + kNN)
	*/
	string nombre_entrada(argv[1]);
	string nombre_salida(argv[2]);
	string metodo_a_utilizar(argv[3]);

	cout << "Levantando datos..." << endl;
	LevantaDatos ld(nombre_entrada);
	testAlphaPCA(0,ld,10);
	//testear(1, ld);

	return 0;
}