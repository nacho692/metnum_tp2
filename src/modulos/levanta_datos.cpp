#include "levanta_datos.h"

string INPUT_FILE_PATH = "tests/";

LevantaDatos::LevantaDatos(string input_file_name, string output_file_name){
	// Levantar inputs
	string line;
	ifstream input_file(INPUT_FILE_PATH + input_file_name);

	if (input_file.is_open()){
		stringstream iss;
		string token;

		getline(input_file, line);
		iss << line;
		getline(iss, token,' ');
		this->input_file_path = token + "train.csv";
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

	// Seteo los nombres de los archivos
	this->output_file_path = INPUT_FILE_PATH + output_file_name;
	this->confusion_file_path = INPUT_FILE_PATH + input_file_name + "_matrices_confusion";
	this->hit_rates_file_path = INPUT_FILE_PATH + input_file_name + "_hit_rates";
	this->ciclos_de_clock_file_path = INPUT_FILE_PATH + input_file_name + "_ciclos"; 	// el de los ciclos
	this->autovalores_file_path = INPUT_FILE_PATH + input_file_name + "_autovalores";		// el de los autovectores


	// Creo los archivos
	ofstream ofs;

	ofs.open(this->output_file_path, std::ofstream::out | std::ofstream::trunc);
	ofs.close();

	ofs.open(this->confusion_file_path, std::ofstream::out | std::ofstream::trunc);
	ofs.close();

	ofs.open(this->hit_rates_file_path, std::ofstream::out | std::ofstream::trunc);
	ofs.close();

	ofs.open(this->ciclos_de_clock_file_path, std::ofstream::out | std::ofstream::trunc);
	ofs.close();

	ofs.open(this->autovalores_file_path, std::ofstream::out | std::ofstream::trunc);
	ofs.close();


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

void LevantaDatos::EscribirResultados(int clocks_para_seteo_cambio_base, int clocks_para_reconocimiento,	Matriz matriz_confusion, vector<double> hit_rates){
	ofstream ofs_ciclos;
	ofs_ciclos.open(this->ciclos_de_clock_file_path, std::ofstream::out | std::ofstream::app);
	ofs_ciclos << clocks_para_seteo_cambio_base << " " << clocks_para_reconocimiento << endl;
	ofs_ciclos.close();

	ofstream ofs_confusion;
	ofs_confusion.open(this->confusion_file_path, std::ofstream::out | std::ofstream::app);
	ofs_confusion << matriz_confusion << endl;
	ofs_confusion.close();

	ofstream ofs_hit_rates;
	ofs_hit_rates.open(this->hit_rates_file_path);
	for (int i = 0; i < 10; i++){
		ofs_hit_rates << hit_rates[i];
	}
	ofs_hit_rates << endl;
	ofs_hit_rates.close();

}

string LevantaDatos::FilePath() const{
	return this->input_file_path;
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