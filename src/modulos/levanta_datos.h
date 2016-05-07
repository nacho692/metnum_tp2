#ifndef LEVANTA_DATOS_H_
#define LEVANTA_DATOS_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "digito.h"

using namespace std;

class LevantaDatos{
	private:
		vector<Digito> training_values;

	public:
		LevantaDatos();
};

#endif