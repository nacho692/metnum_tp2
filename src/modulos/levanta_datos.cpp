#include "levanta_datos.h"

#define INPUT_FILE_PATH "tests/test1.in"

LevantaDatos::LevantaDatos(){
	// Levantar inputs
	string line;
	ifstream input_file(INPUT_FILE_PATH);

	if (input_file.is_open()){
		stringstream iss;
		string token;

		getline(input_file, line);
		iss << line;
		getline(iss, token,' ');
		this->file_path = token + "train.csv";
		getline(iss, token,' ');
		this->cantidad_vecinos = (unsigned int) stoi(token);
		getline(iss, token,' ');
		this->alpha = (unsigned int) stoi(token);
		getline(iss, token,' ');
		this->gamma = (unsigned int) stoi(token);
		getline(iss, token);
		this->cantidad_folds = (unsigned int) stoi(token);

		iss.clear();


		while ( getline (input_file,line) ){
			vector<unsigned int> fold;

			iss << line;
			while ( getline (iss, token, ' ') ){
				fold.push_back(stoi(token));
			}
			this->folds.push_back(fold);

			iss.clear();
		}

		input_file.close();
	} else {
		cout << "No se abre el input" << endl;
	}

	// Levantar d´igitos

	string linea;
	ifstream data_file(this->FilePath());

	if (data_file.is_open()){
		getline(data_file, linea);

		data_file.close();
	} else {
		cout << "No se abre la data" << endl;
	}

}

string LevantaDatos::FilePath() const{
	return this->file_path;
}

unsigned int LevantaDatos::CantidadVecinos() const{
	return this->cantidad_vecinos;
}

unsigned int LevantaDatos::Alpha() const{
	return this->alpha;
}
unsigned int LevantaDatos::Gamma() const{
	return this->gamma;
}
unsigned int LevantaDatos::CantidadFolds() const{
	return this->cantidad_folds;
}