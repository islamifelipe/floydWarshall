/*
#=======================================================================
# Islame Felipe DA COSTA FERNANDES --- Copyright 2017
#-----------------------------------------------------------------------
#
# This code implements The Floyd-Warshall algorithm.
#
#=======================================================================
*/


/*
	Observacoes:
		-1 ==> NIL
		MAX_INT ==> infinito
*/


#include <stdio.h> 
#include <map> 
#include <list>
#include <string>
#include <vector>
#include <cmath>
#include <stack>   
#include <utility>      // std::pair
#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

/*recebe duas matrizes n por n.
Copia a matriz original na matriz copia*/
void copie(int n, double **original, double **copia){
	if (original!=NULL && copia!=NULL){
		for (int i=0; i<n; i++){
			if (original[i]!=NULL && copia[i]!=NULL){
				for (int j=0; j<n; j++){
					copia[i][j] = original[i][j];
				}
			} else {
				cerr<<"ERRO NA COPIA!"<<endl;
				exit(1);
			}
		}
	} else {
		cerr<<"ERRO NA COPIA!"<<endl;
		exit(1);
	}

}


/* recebe n, a quantidade de vértices e a dimensao de w
e w a matriz de pesos. 
Retorna a matriz (um ponteiro para ponteiro) dos pesos do caminho da linha i para a coluna j
A matriz W é tal que W[i][j] = 0 se i == j; W[i][j]=MAX_INT se nao existe aresta de i pra j; W[i][j]=cij se existe aresta i pra j
A matriz PTH é a matriz de predecessores que ajudará a construir o caminho. Ja vem alocada
*/
double **floydWarshall(int n, double **W, double **PTH){
	/*Esta implementaçao utiliza apenas duas matrizes auxiliares. D é a matriz corrente. Dant é a matriz anterior*/
	/*W nao é modificada*/
	double **D, **Dant, **PTHant;
	D 		= new double*[n]; // D
	Dant 	= new double*[n]; // Daux
	PTHant  = new double*[n];
	for (int i=0; i<n; i++){
		D[i] 		= new double[n];
		Dant[i] 	= new double[n];
		PTHant[i] 	= new double[n];
	}

	copie(n, W, Dant); // copia w em D; D^inicial

	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			if (i!=j && W[i][j]<INT_MAX){
				PTHant[i][j] = i+1;
			} else {
				PTHant[i][j] = -1;
			}
		}
	}

	for (int k = 0; k<n; k++){
		for (int i = 0; i<n; i++){
			for (int j = 0; j<n; j++){
				if (Dant[i][j]<=Dant[i][k] + Dant[k][j]){
					D[i][j] = Dant[i][j];
					PTH[i][j] = PTHant[i][j];	
				} else {
					D[i][j] = Dant[i][k] + Dant[k][j];
					PTH[i][j] = PTHant[k][j];
				}
			}
		}
		copie(n, D, Dant);
		copie(n, PTH, PTHant);
	}

	delete[] Dant;
	delete[] PTHant;
	return D;

}

/*a matriz PTH deve ser a matriz de predecessores (intermediarios) definida no CORMEM seçao 25.2*/
/*n é a dimensao da matriz. -1 representa NIL
i e j vao de 1 a n*/
void printCaminho(double **PTH, int i, int j, int n){
	stack<int> pilha;
	i--;
	j--;
	while (i!=j && PTH[i][j]!=-1){
		pilha.push(j);
		j =  PTH[i][j]-1;
	}
	if (i==j){
		cout<<i+1<<" ";
		while (pilha.empty()==false){
			int p = pilha.top();
			pilha.pop();
			cout<<p+1<<" ";
		}
		cout<<endl;
	}
}

void printMatriz(int n, double **W){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cout<<W[i][j]<<" ";
		}
		cout<<endl;
	}
}

int main(int argc, const char * argv[]){
	// if (argc != 2) {
 //        cout << "Parameter error. Usage: " << argv[0] << " input file " << endl;
 //        exit (1);
 //    }

	ifstream arquivo(argv[1]);
	int n;
	arquivo>>n;
	double **W = new double*[n];
	double **PTH = new double*[n];
	for(int i=0; i<n; i++){
		W[i] = new double[n];
		PTH[i]  = new double[n];
		for(int j=0; j<n; j++){
			if (i==j) W[i][j] =0;
			else W[i][j] = INT_MAX;
		}
	}
	/*O arquivo de entrada nao precisa ter os valores infitido nem ii=0 (?)*/
	int i, j, c; // o arquivo de entrada tem valores i j entre 1 e n
	while (arquivo>>i){
		arquivo>>j;
		arquivo>>c;
		if (i<=n && i>=1 && j<=n && j>=1){
			W[i-1][j-1] = c;
		}
	}
	double **D = floydWarshall(n, W, PTH);
	printMatriz(n, D);
	cout<<endl;
	printMatriz(n, PTH);
	cout<<"Caminho mais curto de de 5 pra 3 : "<<endl;
	printCaminho(PTH, 5, 3, n);
	cout<<"Caminho mais curto de de 3 pra 2 : "<<endl;
	printCaminho(PTH, 3, 2, n);
	cout<<"Caminho mais curto de de 2 pra 1 : "<<endl;
	printCaminho(PTH, 2, 1, n);
	cout<<"Caminho mais curto de de 2 pra 3 : "<<endl;
	printCaminho(PTH, 2, 3, n);

	return 0;
}