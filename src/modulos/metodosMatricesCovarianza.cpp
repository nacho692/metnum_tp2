#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include "../utils/matriz.h"
/*
Descripcion:
	Calculamos el vector μ que contiene la media de cada de una las variables.
Input:
	@Param1: Matriz ( vector<Vector> ) M de R^n*m.
Output:
	@Vector: new vector v de R^1*m. Donde v[i]= (M[i][0] + m[i][1] + ... + m[i][n]) / CantFilas(M)
Obs:
	Vector esta en dinamica. Hay que hacerle un Free despues.
*/
Vector getVectorDeMedias(const Matriz& set){
	
	Vector v = Vector( set.Ancho() );
	v = set[0]; // v = M[0]
	
	for(int i = 0; i < set.Alto(); i++){
		v = v + set[i]; 
	}	
	// (Para todo 0 <= i <= m)  v[i] = M[i][0] + m[i][1] + ... + m[i][n]


	//TODO: Esto debería ser una funcion de La clase Vector
	//TODO: Y claramente en Matriz
	double n = 1 / set.Alto(); // n = 1 / Cantfilas(M)
	for(int i = 0; i < set.Ancho(); i++){
		v[i] = v[i] * n;
	}
	// (Para todo 0 <= i <= m)  v[i] = ( M[i][0] + m[i][1] + ... + m[i][n] ) / CantFilas(M)

	return v;
}

/*
Descripcion:
	Construimos la matriz X ∈ R n×m. Donde cada muestra corresponde a una fila de X 
	y tienen media cero (i.e., x[i] := x[i] − μ ).
Input:
	@Param1: Matriz ( vector<Vector> ) M de R^n*m. Variables * Pixeles.
	@Param2: Vector ( vector<Double> ) v de R^1*m. Contiene la media de cada de una las variables.
Post:
	@Output(M)[i][j] = @Input(M)[i][j] - v[j]
*/
void getMatrizConMedia0(const Matriz& set, Matriz& M, const Vector& v){

	for(int i = 0; i < set.Alto(); i++)
		for(int j = 0; j < set.Ancho(); j++)
			M[i][j] = M[i][j] - v[j];

}

/*
Descripcion:
	Construimos la matriz Mx ∈ R m×m. Donde Mx = Xt * X.
Input:
	@Param1: Matriz ( vector<Vector> ) X de R^n*m. Variables * Pixeles.
Post:
	@Output(X)[i][j] = @Input(X)trasponer()[i] * @Input(X)[i] / 1/cantfilas(X)
*/
Matriz getMatrizCovarianzaPCA( Matriz& X){

	Matriz Xt = X; 
	Xt.Transponer();	//Xt == X.trasponer()
	
	X = Xt * X; //X = Xt * X
	
	double n = 1 / ( X.Alto() - 1 );
	X = X*n;	//X = Xt * X * (1/n-1) 

}


void PCA(const Matriz& set,const unsigned int alpha){

	Matriz M = set;
	//Calculamos el vector μ ("vectorDeMediasPorCols") que contiene la media de cada de una las variables.
	Vector vectorDeMediasPorCols = getVectorDeMedias(M);	

	/*
	Construimos la matriz X ∈ R n×m. Donde cada muestra corresponde a una fila de X 
	y tienen media cero (i.e., x (i) := ( x(i) − μ) / ( (n − 1)^(1/2) ).
	No voy a dividir ahora para hacerlo después directo cuando multiplico Xt * X
	*/
	getMatrizConMedia0(set, M, vectorDeMediasPorCols);

	/*
	Construimos matrizCovarianza = (Xt * X) * (1/n-1)
	*/
	Matriz matrizCovarianza = getMatrizCovarianzaPCA(M);
	//Obs: matrizCovarianza es cuadrada. matrizCovarianza e R^m*m

	/*
	Conseguimos los alpha's autovalores mas grandes, y sus autovectores asociados.
	Matriz P = ( autovec1, autovec2, ..., autovecn ). Donde autovec e R1*n y es el autovector asociado al autovalor i-esimo.
	*/
	Matriz matrizDiagonal = Matriz ( alpha, alpha);
	Matriz matrizCambioBase = Matriz ( alpha, matrizCovarianza.Ancho());
	Matriz matrizDeflacion = Matriz();

	for(int i = 0; i < alpha ; i++){
		//Consigo un vector random
		Vector autovector(alpha);
		autovector.RandomVector();
		//no tengo para hacer vector * vector traspuesto, debería ser un constructor de Matriz
		matrizDiagonal[i][i] =  matrizCovarianza.MetodoPotenciaNIteraciones( autovector, 3);
		//autovector esta asociado al autovalor[i]
		//No me queda claro si esto es por copia o por referencia asique uso new en random
		matrizCambioBase[i] = autovector;
		//Necesito hacer un constructor para esto.
		matrizDeflacion[i] = matrizDeflacion[i] - autovector * autovector * matrizDiagonal[i][i];
		matrizCovarianza = matrizCovarianza - matrizDeflacion;
	}
	/*
	matrizCambioBase es una matriz con filas [v1t,v2t,v3t,v4t,v5t,...,valphat] 
	Donde Vi es un autovector en R^alpha*m asociado al autovalor i-esimo ( que esta en matrizDiagonal[i][i] )

	matrizDiagonal tiene los alpha's mayores autovalores en la diagonal. Lo demas es 0.
	*/

}