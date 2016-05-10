#include "modulos/identificador.h"
#include "modulos/levanta_datos.h"
int main(){
	LevantaDatos ld;
	ld.SetearKesimoFold(0);

	Matriz mt = ld.MatrizTraining();
	Identificador id(ld.LabelsTraining(),ld.CantidadVecinos());
	id.PLS_DA(mt,5);
	for(unsigned int i = 0; i < 10; i++){
		cout << ld.LabelsTesting()[i] << endl;
		cout << id.kNN(ld.MatrizTesting()[i]) << endl;
	}
	return 0;
}