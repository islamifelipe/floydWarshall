/*
#=======================================================================
# Islame Felipe DA COSTA FERNANDES --- Copyright 2017
#-----------------------------------------------------------------------
#
# This code implements The Floyd-Warshall algorithm.
#
#=======================================================================
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
A matriz W é tal que W[i][j] = 0 se i == j; W[i][j]=MAX_INT se nao existe aresta de i pra j; W[i][j]=cij se existe aresta i pra j*/
double **floydWarshall(int n, double **W){
	/*Esta implementaçao utiliza apenas duas matrizes auxiliares. D é a matriz corrente. Dant é a matriz anterior*/
	/*W nao é modificada*/
	double **D, **Dant;
	D 		= new double*[n]; // D
	Dant 	= new double*[n]; // Daux
	for (int i=0; i<n; i++){
		D[i] 		= new double[n];
		Dant[i] 	= new double[n];
	}

	copie(n, W, Dant); // copia w em D; D^inicial
	for (int k = 0; k<n; k++){
		for (int i = 0; i<n; i++){
			for (int j = 0; j<n; j++){
				if (Dant[i][j]< Dant[i][k] + Dant[k][j]){
					D[i][j] = Dant[i][j];
				} else {
					D[i][j] = Dant[i][k] + Dant[k][j];
				}
			}
		}
		copie(n, D, Dant);
	}

	delete[] Dant;
	return D;

}

/*a matriz PTH deve ser a matriz de predecessores (intermediarios) definida no CORMEM seçao 25.2*/
void printCaminho(){

}

int main(){
	
	return 0;
}