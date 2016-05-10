#include "escupe_datos.h"

string OUTPUT_FILE_PATH = "tests/";

EscupeDatos::EscupeDatos(string output_file_name){
	fstream file;
	file.open(OUTPUT_FILE_PATH + output_file_name);
	
	file << OUTPUT_FILE_PATH + output_file_name;
	file.close();
}