#include "identificador.h"

Identificador::Identificador( vector<int> clases){
	this->clases = clases;
//	this->cantidad_vecinos = cantidad_vecinos;
//	this->gamma = gamma;
//	this->alpha = alpha;
}

void Identificador::SinMetodo(const Matriz& set){
	this->tSet = set;
	//Cambio de base es identidad, queda todo
	this->Vt = Matriz(set.Ancho(),set.Ancho());
	for(unsigned int i = 0; i < Vt.Alto(); i++){
		for(unsigned int j = 0; j < Vt.Ancho(); j++){
			this->Vt[i][j] = (i==j);
		}
	}
	this->Vt.Identidad(true);
}

void Identificador::PCA(const Matriz& set, unsigned int alpha){
	Matriz X = set;
	this->medias = CentrarDividir(X);
	Matriz Xt = set.Transponer();

	Matriz mCovarianza = Xt*X;
	Vector autovector = Vector( set.Ancho() );
	Matriz mDeflacion;
	double autovalor;
	this->Vt = Matriz ( mCovarianza.Alto(), alpha);
	this->autovalores = Vector(alpha);
	for(unsigned int i = 0; i < alpha; i++){
		autovector.RandomVector();
		autovalor =  mCovarianza.MetodoPotenciaEpsilon(autovector,0.00003,100);
		this->autovalores[i] = autovalor;
		this->Vt[i] = autovector;
		mDeflacion = Matriz( autovector, autovector *autovalor );
		mCovarianza = mCovarianza - mDeflacion;
	}
	//Mi cambio de base Vt
	//Actualizo el training set 
	tSet = (Vt*Xt).Transponer();
	//tSet = tSet.Transponer();
}

void Identificador::PLS_DA(const Matriz& set, unsigned int gamma ){
	Matriz X = set;
	this->medias = CentrarDividir(X);
	Matriz Xt = set.Transponer();

	Matriz Y(10,set.Alto());

	for(unsigned int i = 0; i < Y.Alto(); i++){
		for(unsigned int j = 0; j < Y.Ancho(); j++){
			Y[i][j] = -1/sqrt(set.Alto()-1);
		}
		Y[i][Clases()[i]] = 1/sqrt(set.Alto()-1);
		Y[i] = Y[i] - medias;
	}

	CentrarDividir(Y);
	Matriz Yt = Y.Transponer();

	this->Vt = Matriz(set.Ancho(), gamma);
	this->autovalores = Vector(gamma);
	for(unsigned int i = 0; i < gamma; i++){
		//Matriz M = Xt*Y*Yt*X = At*A
		Matriz A = Yt*X;
		Matriz M = A.Transponer()*A;

		Vector w = Vector( M.Ancho() );
		w.RandomVector();
		this->autovalores[i] = M.MetodoPotenciaEpsilon(w,0.00003,100);

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


Vector Identificador::CentrarDividir(Matriz& X) const{
	//Esto es igual en ambos metodos
	Matriz Xt = X.Transponer();
	double escalar = 1 / sqrt( X.Alto()-1 );
	Vector med = Vector(Xt.Alto());

	for(unsigned int i = 0; i < Xt.Alto(); i++){
		double media = Xt[i].Media();
		med[i] = media;
		for(unsigned int j = 0; j < Xt.Ancho(); j++){
			Xt[i][j] -= media;
			Xt[i][j] *= escalar;
		}
	}

	X = Xt.Transponer();
	return med;
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


int Identificador::kNN(const Vector& v, unsigned int kVecinos) const{

	//Cambio de base
	Vector vb = v;
	if(!this->Vt.Identidad())
		vb = (v - this->medias)*(1/sqrt(tSet.Alto()-1));
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
	for(unsigned int i = 0; i < kVecinos; i++){
		pop_heap(distancias.begin(), distancias.end(),cmpVecinoDistancia);
		vecinos.push_back(distancias[distancias.size()-1]);
		distancias.pop_back();
	}

	//Por si ya lo teniamos cargado en el training set basicamente
	if(dEq(vecinos[0].distancia)){
		return vecinos[0].clase;
	}

	//Ordenamos para juntar cada clase y asi sacar el voto calificado mas facil (no tengo acentos)

	vector<double> votos(10);
	for(unsigned int i = 0; i < vecinos.size(); i++){
		votos[vecinos[i].clase] += 1/vecinos[i].distancia;
	}
	unsigned int maxD = 0;
	double maxV = 0;
	for(unsigned int i = 0; i < votos.size(); i++){
		if(votos[i] > maxV){
			maxV = votos[i];
			maxD = i;
		}
	}

	return maxD;
}



const vector<int>& Identificador::Clases()const{
	return this->clases;
}

