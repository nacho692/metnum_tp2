#include "identificador.h"

Identificador::Identificador( vector<int> clases, unsigned int cantidad_vecinos, unsigned int alpha, unsigned int gamma){
	this->clases = clases;
	this->cantidad_vecinos = cantidad_vecinos;
	this->gamma = gamma;
	this->alpha = alpha;
}

void Identificador::PCA(const Matriz& set){
	Matriz X,Xt;
	CentrarDividir(set,X,Xt);
	
	Matriz mCovarianza = Xt*X;
	Vector autovector = Vector( Alpha() );
	Matriz mDeflacion;
	double autovalor;
	this->Vt = Matriz ( Alpha(), mCovarianza.Ancho());

	for(int i = 0; i < Alpha() ; i++){
		autovector.RandomVector();
		autovalor =  mCovarianza.MetodoPotenciaNIteraciones( autovector, 3);
		Vt[i] = autovector;
		mDeflacion = Matriz( autovector, autovector) * autovalor;
		mCovarianza = mCovarianza - mDeflacion;
	}

	//Mi cambio de base Vt
	//Actualizo el training set 
	this->tSet = Vt*Xt;
}

void Identificador::PLS_DA(const Matriz& set ){
	Matriz X,Xt;
	CentrarDividir(set,X,Xt);

	Matriz Yt;
	Matriz Y(10,set.Alto());

	for(unsigned int i = 0; i < Y.Alto(); i++){
		for(unsigned int j = 0; j < Y.Ancho(); j++){
			Y[i][j] = -1;
		}
		Y[i][Clases()[i]] = 1;
	}

	Yt = Y;
	Yt.Transponer();

	Matriz XC = Xt;
	Vt = Matriz( set.Ancho(), Gamma());
	for(unsigned int i = 0; i < Gamma(); i++){
		Matriz M = Xt*Y*Yt*X;
		Vector w = Vector( M.Ancho() );
		
		w.RandomVector();
		M.MetodoPotenciaNIteraciones(w,5);
		w = w * (1/w.Norma());

		Vector t = X*w;
		t = t * (1/t.Norma());

		Matriz T = Matriz(t,t);
		X = X - (T*X);
		Y = Y - (T*Y);
		Vt[i] = w;
	}

	//Tengo mi transformacion
	//Actualizo el training set
	tSet = Vt*XC;
}

void Identificador::CentrarDividir(const Matriz& set, Matriz& X, Matriz& Xt){
	//Esto es igual en ambos metodos
	Xt = set;
	Xt.Transponer();
	double escalar = 1 / sqrt( set.Alto()-1 );
	this->medias = Vector(Xt.Alto());

	for(unsigned int i = 0; i < Xt.Alto(); i++){
		//TODO: Vector + escalar
		double media = Xt[i].Media();
		this->medias[i] = media;
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
		d.clase = Clases()[i];
		distancias.push_back(d);
	}

	make_heap(distancias.begin(),distancias.end(),cmpVecinoDistancia);

	vector<Vecino> vecinos;
	for(unsigned int i = 0; i < Cantidad_Vecinos(); i++){
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

unsigned int Identificador::Alpha()const{
	return this->alpha;
}
unsigned int Identificador::Gamma()const{
	return this->gamma;
}
unsigned int Identificador::Cantidad_Vecinos()const{
	return this->cantidad_vecinos;
}
const vector<int>& Identificador::Clases()const{
	return this->clases;
}
