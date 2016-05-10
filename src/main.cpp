#include "modulos/identificador.h"
#include "modulos/escupe_datos.h"
#include "modulos/levanta_datos.h"
int main(int argc, char const *argv[]){
	std::string nombre_entrada(argv[1]);
	std::string nombre_salida(argv[2]);
	std::string metodo_a_utilizar(argv[3]);		//(0: kNN , 1: PCA + kNN ,2: PLS-DA + kNN)

	// LevantaDatos ld(nombre_entrada);
	// ld.SetearKesimoFold(0);

	// Matriz mt = ld.MatrizTraining();
	// Identificador id(ld.LabelsTraining(),ld.CantidadVecinos());

	// id.PCA(mt, ld.Alpha())
	// for(unsigned int i = 0; i < 10; i++){
	// 	cout << ld.LabelsTesting()[i] << endl;
	// 	cout << id.kNN(ld.MatrizTesting()[i]) << endl;
	// }

	EscupeDatos ep(nombre_salida);

	return 0;
}