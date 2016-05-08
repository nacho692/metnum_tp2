
#include "identificador.h"
void Identificador::PLS_DA(const Matriz& set, unsigned int gamma){
	Matriz X,Xt;
	CentrarDividir(set,X,Xt);

	Matriz Yt;
	Matriz Y(10,set.Alto());

	for(unsigned int i = 0; i < Y.Alto(); i++){
		for(unsigned int j = 0; j < Y.Ancho(); j++){
			Y[i][j] = -1;
		}
		Y[i][clases[i]] = 1;
	}

	Yt = Y;
	Yt.Transponer();

	Matriz XC = X;
	Vt = Matriz(set.Ancho(),gamma);
	for(unsigned int i = 0; i < gamma; i++){
		Matriz M = Xt*Y*Yt*X;
		//TODO: Hacerlo random
		Vector w = Vector(M.Ancho());
		M.MetodoPotenciaNIteraciones(w,5);
		w = w * (1/w.Norma());

		Vector t = X*w;
		t = t * (1/t.Norma());
		//TODO: Vector por vector
		//X = X + (-1)*(t*(t*X));
		//Y = Y + (-1)*(t*(t*Y));
		Vt[i] = w;
	}

	//Tengo mi transformacion
	//Actualizo el training set
	tSet = Vt*XC;
}

void Identificador::CentrarDividir(const Matriz& set, Matriz& X, Matriz& Xt) const{
	//Esto es igual en ambos metodos
	Xt = set;
	Xt.Transponer();
	double escalar = 1/sqrt(set.Alto());

	for(unsigned int i = 0; i < Xt.Alto(); i++){
		//TODO: Vector + escalar
		double media = Xt[i].Media();
		for(unsigned int j = 0; j < Xt.Ancho(); j++){
			Xt[i][j] -= media;
			Xt[i][j] *= escalar;
		}
	}

	X = Xt;
	X.Transponer();
}

const Matriz& Identificador::cambioBase() const{
	return Vt;
}

const Matriz& Identificador::trainingSet() const{
	return tSet;
}

int Identificador::kNN(const Vector& v) const{
	//TODO: Cambio de base con V
	Vector vb = Vt*v;

	vector<Vecino> distancias;
	for(unsigned int i = 0; i < tSet.Alto(); i++){
		Vecino d;
		d.distancia = vb.Distancia(tSet[i]);
		d.clase = clases[i];
		distancias.push_back(d);
	}

	make_heap(distancias.begin(),distancias.end(),cmpVecinoDistancia);

	vector<Vecino> vecinos;
	for(unsigned int i = 0; i < cantidad_vecinos; i++){
		pop_heap(distancias.begin(), distancias.end(),cmpVecinoDistancia);
		vecinos.push_back(distancias[distancias.size()-1]);
		distancias.pop_back();
	}

	//Por si ya lo teniamos cargado en el training set basicamente
	if(dEq(vecinos[0].distancia)){
		return vecinos[0].clase;
	}

	//Ordenamos para juntar cada clase y asi sacar el voto calificado mas facil (no tengo acentos)
	sort(vecinos.begin(),vecinos.end(),cmpVecinoClase);
	double max = 0;
	double sum = 0;
	int claseMax;
	int clase = vecinos[0].clase;
	for(unsigned int i = 0; i < vecinos.size(); i++){
		//Si llegue al final o si cambio de clase, me fijo si supera al maximo anterior
		if(clase != vecinos[i].clase || i == vecinos.size()-1){
			//Sumo el ultimo si es la ultima vuelta
			sum += (1/vecinos[i].distancia)*(i== vecinos.size()-1); 
			if(sum > max){
				max = sum;
				claseMax = clase;
			}
			sum = 0;
			clase = vecinos[i].clase;
		}
		sum += (1/vecinos[i].distancia);
	}

	return claseMax;
}
