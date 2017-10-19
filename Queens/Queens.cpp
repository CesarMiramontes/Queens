// Queens.cpp: archivo de proyecto principal.

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#define N 12

using namespace System;
using namespace std;

int solutions = 0;
long int total_iterations = 0;
float total_time;
clock_t begin_time;
clock_t last_result;

void solver(bool **tablero, char **piezas, int row, int n);
void solver(bool **tablero, int row);
bool **board(bool **tablero);
char **pieza(char **piezas);
void display_board(char **tablero);
void check_cell(int a, int b, bool **tablero);

int main(int argc, char** argv) {
	//const clock_t begin_time = clock();	
	bool **tablero;
	char **piezas;
	tablero = new bool*[N];
	piezas = new char*[N];
	int n = N / 2;
	for (int i = 0; i < N; i++) {
		tablero[i] = new bool[N];
		piezas[i] = new char[N];
		for (int j = 0; j < N; j++) {
			tablero[i][j] = true;
			piezas[i][j] = '.';
		}
	}
	
	begin_time = clock();
	solver(tablero, piezas, 0, n);
	total_time = float(clock() - begin_time) / CLOCKS_PER_SEC;

	cout << "Soluciones encontradas: " << solutions * 2 << endl;
	cout << "Tiempo total transcurrido: " << total_time << " segs" << endl;
	cout << "Numero de iteraciones: " << total_iterations << endl;
	//cout << "Tiempo desde el ultimo resultado: " << float(clock() - last_result) / CLOCKS_PER_SEC << endl;
	system("pause");
	return 0;
}

bool **board(bool **tablero) {
	bool **auxtablero;
	auxtablero = new bool*[N];
	for (int i = 0; i < N; i++) {
		auxtablero[i] = new bool[N];
		for (int j = 0; j < N; j++) {
			auxtablero[i][j] = tablero[i][j];
		}
	}
	return auxtablero;
}

char **pieza(char **piezas) {
	char **auxpiezas;
	auxpiezas = new char*[N];
	for (int i = 0; i < N; i++) {
		auxpiezas[i] = new char[N];
		for (int j = 0; j < N; j++) {
			auxpiezas[i][j] = piezas[i][j];
		}
	}
	return auxpiezas;
}

void display_board(char **tablero) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << tablero[i][j] << " ";
		}
		cout << endl;
	}
}

void solver(bool **tablero, char** piezas, int row, int n) {
	if (row == N) {
		solutions++;
		/*cout << solutions << "\t" << float(clock() - begin_time) / CLOCKS_PER_SEC << " segs, iteracion " << total_iterations << "" << endl;
		display_board(piezas);
		cout << endl;
		cout << endl;
		last_result = clock();*/
	}

	for (int i = row; i < N; i++) {
		for (int j = 0; j < N; j++) {
			total_iterations++;
			//cout << j << " " << i << endl;
			if (tablero[j][i]) {
				//cout << j << " " << i << endl;
				char **auxpiezas = pieza(piezas);
				auxpiezas[j][i] = 'D';
				bool **auxtablero = board(tablero);
				check_cell(j, i, auxtablero);
				solver(auxtablero, auxpiezas, row + 1, N);

				for (int i = 0; i < N; i++)
					delete[]auxpiezas[i];

				for (int i = 0; i < N; i++)
					delete[]auxtablero[i];

				delete[]auxpiezas;
				delete[]auxtablero;
				auxpiezas = NULL;
				auxtablero = NULL;
			}
		}
		break;
	}
}

void solver(bool **tablero, int row) {
	if (row == N) {
		solutions++;
	}

	for (int i = row; i < N; i++) {
		for (int j = 0; j < N; j++) {
			total_iterations++;
			if (tablero[j][i]) {
				bool **auxtablero = board(tablero);
				check_cell(j, i, auxtablero);
				solver(auxtablero, row + 1);

				for (int i = 0; i < N; i++)
					delete[]auxtablero[i];

				delete[]auxtablero;
				auxtablero = NULL;
			}
		}
		break;
	}
}

void check_cell(int a, int b, bool** tablero) {
	/*for (int i = 0; i < N; i++) {
	tablero[i][b] = false;
	}*/

	for (int i = b + 1; i < N; i++) {
		tablero[a][i] = false;
	}

	for (int i = a, j = b; j < N && i < N; i++, j++) {
		tablero[i][j] = false;
	}

	for (int i = a, j = b; j < N && i >= 0; i--, j++) {
		tablero[i][j] = false;
	}

}