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

void testear(int fold, char const *argv[]){

	// Todo : estoy levantando los datos adentros como un boludo
	
	string nombre_entrada(argv[1]);
	LevantaDatos ld(nombre_entrada);
	cout << "Datos levantados.." << endl;

	ld.SetearKesimoFold(fold);
	cout << fold << "-esimo fold seteado para testing.." << endl;

	Matriz mt = ld.MatrizTraining();
	Identificador id(ld.LabelsTraining(),ld.CantidadVecinos());
	id.PCA(mt,100);
	cout << "Preparado identificador para PCA.." << endl;

	Matriz matriz_confusion(10, 10);
	testearTrainingSet(id, ld, matriz_confusion);
	cout << matriz_confusion << endl;
	// EscupeDatos ep(nombre_salida, matriz_confusion);
}

int main(int argc, char const *argv[]){ 
	/* argv
	nombre_entrada
	nombre_salida_utilizar	(0: kNN , 1: PCA + kNN ,2: PLS-DA + kNN)
	*/

	testear(1, argv);

	return 0;
}