#include "levanta_datos.h"

string INPUT_FILE_PATH = "tests/";

LevantaDatos::LevantaDatos(string input_file_name){
	// Levantar inputs
	string line;
	ifstream input_file(INPUT_FILE_PATH + input_file_name);

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

	// Setear los tamaños de matrices y vectores
	this->digitos = Matriz(784, 42000);

	unsigned int cantidad_testing = 42000/this->CantidadFolds();
	unsigned int cantidad_training = 42000 - cantidad_testing;

	digitos_testing = Matriz(784, cantidad_testing);
	labels_testing.resize(cantidad_testing);

	digitos_training = Matriz(784, cantidad_training);
	labels_training.resize(cantidad_training);

	// Levantar d´igitos

	string linea;
	ifstream data_file(this->FilePath());

	if (data_file.is_open()){
		getline(data_file, linea);
		int  i = 0;
		while ( getline(data_file, linea) ){
			stringstream data_line;
			string pixel;

			data_line << linea;

			unsigned int j = 0;
			getline(data_line, pixel, ',');

			this->labels.push_back( stoi(pixel) );

			while ( getline(data_line, pixel, ',') ){
				this->digitos[i][j] = (double) stoi(pixel);
				j++;
			}

			i++;
			data_line.clear();
		}

		data_file.close();
	} else {
		cout << "No se abre la data" << endl;
	}
}

void LevantaDatos::SetearKesimoFold(unsigned int k){
	vector<unsigned int> fold = this->folds[k];
	unsigned int indice_testing = 0;
	unsigned int indice_training = 0;
	for (unsigned int i = 0; i < this->digitos.Alto(); i++){
		unsigned int j;
		if (fold[i]){ // Si es para training
			this->labels_training[indice_training] = this->labels[i];
			for (j = 0; j < 784; j++)
				this->digitos_training[indice_training][j] = this->digitos[i][j];

			indice_training++;
		} else {
			this->labels_testing[indice_testing] = this->labels[i];
			for (j = 0; j < 784; j++)
				this->digitos_testing[indice_testing][j] = this->digitos[i][j];
			
			indice_testing++;
		}
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
const Matriz& LevantaDatos::MatrizTraining() const{
	return this->digitos_training;
}
const vector<int>& LevantaDatos::LabelsTraining() const{
	return this->labels_training;
}
const Matriz& LevantaDatos::MatrizTesting() const{
	return this->digitos_testing;
}
const vector<int>& LevantaDatos::LabelsTesting() const{
	return this->labels_testing;
}