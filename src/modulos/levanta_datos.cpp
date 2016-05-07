#include "levanta_datos.h"

#define TRAINING_FILE_PATH "data/train.csv"
#define TRAINING_FILE_SIZE 40000

LevantaDatos::LevantaDatos(){
	string line;
	ifstream training_file(TRAINING_FILE_PATH);

	int i = 0;
	getline (training_file,line);
	if (training_file.is_open()){
		while ( getline (training_file,line) && i < 2){
			cout << line[0] << endl;
			i++;
		}

		training_file.close();
	} else {
		cout << "no abre nada" << endl;
	}
}