//============================================================================
// Name        : Lab5_concurrent.cpp
// Author      : Amila
// Version     :
// Copyright   : This is for Academic purposes
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
using namespace std;

double **a, **b, **c;
void initArrays(int n);
void cleanUp(int n);
void multiplyMatrix(int n);
void populateArrays(int n);
double fRand(double fMin, double fMax);
int main() {
	int n, i, j;
	cout << "\nEnter the size of rows and columns for Matrix A & B:::\n\n";
	cin >> n;
	initArrays(n);
	populateArrays(n);
	cout << "\n\nMatrix A :\n\n";
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			cout << "\t" << a[i][j];
		}
		cout << "\n\n";
	}

	cout << "\n\nMatrix B :\n\n";
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			cout << "\t" << b[i][j];
		}
		cout << "\n\n";
	}

	cout << "\n-----------------------------------------------------------\n";

	cout << "\n\nMultiplication of Matrix A and Matrix B :\n\n";
	multiplyMatrix(n);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			cout << "\t" << c[i][j];
		}
		cout << "\n\n";
	}
	cleanUp(n);
	return 0;
}
void initArrays(int n) {
	a = new double*[n];
	for (int i = 0; i < n; i++)
		a[i] = new double[n];
	b = new double*[n];
	for (int i = 0; i < n; i++)
		b[i] = new double[n];
	c = new double*[n];
	for (int i = 0; i < n; i++)
		c[i] = new double[n];
}
void populateArrays(int n) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			a[i][j] = fRand(0.0,10.0);
			b[i][j] = fRand(0.0,10.0);
		}
	}
}
void cleanUp(int n) {
	for (int i = 0; i < n; ++i) {
		delete[] a[n];
	}
	delete[] a;
	for (int i = 0; i < n; ++i) {
		delete[] b[n];
	}
	delete[] b;
	for (int i = 0; i < n; ++i) {
		delete[] c[n];
	}
	delete[] c;
}
void multiplyMatrix(int n) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			c[i][j] = 0;
			for (int k = 0; k < n; k++) {
				c[i][j] = c[i][j] + a[i][k] * b[k][j];
			}
		}
	}
}
double fRand(double fMin, double fMax) {
	double f = (double) random() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}
