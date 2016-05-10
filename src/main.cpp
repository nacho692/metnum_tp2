#include "modulos/identificador.h"
#include "modulos/escupe_datos.h"
#include "modulos/levanta_datos.h"

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

	testear(1, ld);

	return 0;
}