/*
Descripcion:
	Calculamos el vector μ que contiene la media de cada de una las variables.
Input:
	@Param1: Matriz ( vector<Vector> ) M de R^n*m.
Output:
	@Vector: new vector v de R^1*m. Donde v[i]= (M[i][0] + m[i][1] + ... + m[i][n]) / Cant_Filas(M)
Obs:
	Vector esta en dinamica. Hay que hacerle un Free despues.
*/
Vector getVectorDeMedias(const Matriz& set){
	
	Vector v = new Vector( set.ancho() );
	v = set[0]; // v = M[0]
	
	for(int i = 0; i < set.alto(); i++){
		v = v + set[i]; 
	}	
	// (Para todo 0 <= i <= m)  v[i] = M[i][0] + m[i][1] + ... + m[i][n]


	//TODO: Esto debería ser una funcion de La clase Vector
	//TODO: Y claramente en Matriz
	double n = 1 / set.alto(); // n = 1 / Cant_filas(M)
	for(int i = 0; i < set.ancho(); i++){
		v[i] = v[i] * n;
	}
	// (Para todo 0 <= i <= m)  v[i] = ( M[i][0] + m[i][1] + ... + m[i][n] ) / Cant_Filas(M)

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
void getMatrizConMedia0( Matriz& M, const Vector& v){

	for(int i = 0; i < set.alto(); i++)
		for(int j = 0; j < set.ancho(); j++)
			v[i][j] = v[i][j] - v[j];

}

/*
Descripcion:
	Construimos la matriz Mx ∈ R m×m. Donde Mx = Xt * X.
Input:
	@Param1: Matriz ( vector<Vector> ) X de R^n*m. Variables * Pixeles.
Post:
	@Output(X)[i][j] = @Input(X)trasponer()[i] * @Input(X)[i] / 1/cant_filas(X)
*/
Matriz getMatrizCovarianzaPCA( Matriz& X){

	Matriz Xt = X; 
	Xt.trasponer();	//Xt == X.trasponer()
	
	X = Xt * X; //X = Xt * X
	
	double n = 1 / ( X.alto() - 1 );
	X = X*n;	//X = Xt * X * (1/n-1) 

}


void PCA(const Matriz& set,const unsigned int alpha){

	Matriz M = set;
	//Calculamos el vector μ ("_vectorDeMediasPorCols") que contiene la media de cada de una las variables.
	Vector _vectorDeMediasPorCols = getVectorDeMedias(M);	

	/*
	Construimos la matriz X ∈ R n×m. Donde cada muestra corresponde a una fila de X 
	y tienen media cero (i.e., x (i) := ( x(i) − μ) / ( (n − 1)^(1/2) ).
	No voy a dividir ahora para hacerlo después directo cuando multiplico Xt * X
	*/
	getMatrizConMedia0(M, _vectorDeMediasPorCols);

	/*
	Construimos _matrizCovarianza = (Xt * X) * (1/n-1)
	*/
	Matriz _matrizCovarianza = getMatrizCovarianzaPCA(M);
	//Obs: _matrizCovarianza es cuadrada. _matrizCovarianza e R^m*m

	/*
	Conseguimos los alpha's autovalores mas grandes, y sus autovectores asociados.
	Matriz P = ( autovec1, autovec2, ..., autovecn ). Donde autovec e R1*n y es el autovector asociado al autovalor i-esimo.
	*/
	Matriz matrizDiagonal = Matriz ( alpha, alpha);
	Matriz matrizCambioBase = Matriz ( alpha, _matrizCovarianza.ancho);

	for(int i = 0; i < alpha ; i++){
		//Consigo un vector random
		Vector _autovector = RandomVector(_matrizCovarianza.ancho);
		//no tengo para hacer vector * vector traspuesto, debería ser un constructor de Matriz
		matrizDiagonal[i][i] = MetodoPotenciaNIteraciones( _autovector, _matrizCovarianza);
		//_autovector esta asociado al autovalor[i]
		//No me queda claro si esto es por copia o por referencia asique uso new en random
		matrizCambioBase[i] = _autovector;
		//Necesito hacer un constructor para esto.
		Matriz _matrizDeflacion = _autovector * _autovector * _autovalores[i];
		_matrizCovarianza = _matrizCovarianza - _matrizDeflacion;
	}
	/*
	matrizCambioBase es una matriz con filas [v1t,v2t,v3t,v4t,v5t,...,valphat] 
	Donde Vi es un autovector en R^alpha*m asociado al autovalor i-esimo ( que esta en matrizDiagonal[i][i] )

	matrizDiagonal tiene los alpha's mayores autovalores en la diagonal. Lo demas es 0.
	*/

}