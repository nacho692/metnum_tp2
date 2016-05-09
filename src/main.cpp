#include "modulos/identificador.h"
#include "modulos/levanta_datos.h"
int main(){
	LevantaDatos ld;
	ld.SetearKesimoFold(0);

	Matriz mt = ld.MatrizTesting();
	Identificador id(ld.LabelsTesting(),ld.CantidadVecinos());
	id.PLS_DA(mt,1);
	/*for(unsigned int i = 0; i < 10; i++){
		cout << ld.LabelsTesting()[i] << endl;
		cout << id.kNN(ld.MatrizTesting()[i]) << endl;
	}*/
	return 0;
}