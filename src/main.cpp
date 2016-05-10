#include "modulos/identificador.h"
#include "modulos/escupe_datos.h"
#include "modulos/levanta_datos.h"

using namespace std;

void testearTrainingSet(Identificador& id, LevantaDatos& ld, Matriz& hit_rate){
	// for(unsigned int i = 0; i < ld.LabelsTesting().size(); i++){
	for(unsigned int i = 0; i < ld.LabelsTesting().size(); i++){
		int label =  ld.LabelsTesting()[i];
		int res = id.kNN(ld.MatrizTesting()[i]);
		hit_rate[res][label]++;
	}	
}

int main(int argc, char const *argv[]){ 
	/* argv
	nombre_entrada
	nombre_salida_utilizar	(0: kNN , 1: PCA + kNN ,2: PLS-DA + kNN)
	*/
	string nombre_entrada(argv[1]);
	LevantaDatos ld(nombre_entrada);
	ld.SetearKesimoFold(0);
	Matriz mt = ld.MatrizTraining();
	Identificador id(ld.LabelsTraining(),ld.CantidadVecinos());
	id.PCA(mt,784);
	cout << "Seteado" << endl;
	Matriz hit_rate(10, 10);
	testearTrainingSet(id, ld, hit_rate);
	EscupeDatos ep(nombre_salida, hit_rate);

	return 0;
}