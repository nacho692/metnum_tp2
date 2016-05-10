#include "identificador.h"

Identificador::Identificador( vector<int> clases, unsigned int cantidad_vecinos){
	this->clases = clases;
	this->cantidad_vecinos = cantidad_vecinos;
//	this->gamma = gamma;
//	this->alpha = alpha;
}

void Identificador::SinMetodo(const Matriz& set){
	Matriz X,Xt;
	CentrarDividir(set,X,Xt);
	this->tSet = X;
	//Cambio de base es identidad, queda todo
	this->Vt = Matriz(X.Ancho(),X.Ancho());
	for(unsigned int i = 0; i < Vt.Alto(); i++){
		for(unsigned int j = 0; j < Vt.Ancho(); j++){
			this->Vt[i][j] = (i==j);
		}
	}
}

void Identificador::PCA(const Matriz& set, unsigned int alpha){
	Matriz X,Xt;
	
	CentrarDividir(set,X,Xt);
	Matriz mCovarianza = Xt*X;
	Vector autovector = Vector( set.Ancho() );
	Matriz mDeflacion;
	double autovalor;
	this->Vt = Matriz ( mCovarianza.Alto(), alpha);
	this->autovalores = Vector(alpha);
	for(unsigned int i = 0; i < alpha; i++){
		autovector.RandomVector();
		autovalor =  mCovarianza.MetodoPotenciaNIteraciones( autovector, 10);
		this->autovalores[i] = autovalor;
		this->Vt[i] = autovector;
		mDeflacion = Matriz( autovector, autovector * autovalor );
		mCovarianza = mCovarianza - mDeflacion;
	}
	//Mi cambio de base Vt
	//Actualizo el training set 
	tSet = (Vt*Xt).Transponer();
	//tSet = tSet.Transponer();
}

void Identificador::PLS_DA(const Matriz& set, unsigned int gamma ){
	Matriz X,Xt;
	CentrarDividir(set,X,Xt);

	Matriz Y(10,set.Alto());

	for(unsigned int i = 0; i < Y.Alto(); i++){
		for(unsigned int j = 0; j < Y.Ancho(); j++){
			Y[i][j] = -1;
		}
		Y[i][Clases()[i]] = 1;
	}
	Matriz Yt = Y.Transponer();

	this->Vt = Matriz(set.Ancho(), gamma);
	this->autovalores = Vector(gamma);
	for(unsigned int i = 0; i < gamma; i++){
		//Matriz M = Xt*Y*Yt*X = At*A
		Matriz A = Yt*X;
		Matriz M = A.Transponer()*A;

		Vector w = Vector( M.Ancho() );
		w.RandomVector();
		this->autovalores[i] = M.MetodoPotenciaNIteraciones(w,10);

		w = w * (1/w.Norma());
		Vt[i] = w;

		Vector t = X*w;
		t = t*(1/t.Norma());

		//t*t^t*X = t*(tt*X)
		X = X - Matriz(t,t*X);
		Y = Y - Matriz(t,t*Y);
		Yt = Y.Transponer();
	}

	//Tengo mi transformacion
	//Actualizo el training set
	tSet = (Vt*Xt).Transponer();

}


void Identificador::CentrarDividir(const Matriz& set, Matriz& X, Matriz& Xt){
	//Esto es igual en ambos metodos
	Xt = set.Transponer();
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

	X = Xt.Transponer();
}

const Matriz& Identificador::cambioBase() const{
	return Vt;
}

const Matriz& Identificador::trainingSet() const{
	return tSet;
}


const Vector& Identificador::AutoValores() const{
	return autovalores;
}


int Identificador::kNN(const Vector& v) const{

	Vector vb = (v - this->medias)*(1/sqrt(tSet.Alto()-1));
	//Cambio de base
	vb = Vt*vb;
	vb.Resize(Vt.Alto());
	
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
/*
unsigned int Identificador::Alpha()const{
	return this->alpha;
}
unsigned int Identificador::Gamma()const{
	return this->gamma;
}*/
unsigned int Identificador::Cantidad_Vecinos()const{
	return this->cantidad_vecinos;
}
const vector<int>& Identificador::Clases()const{
	return this->clases;
}
