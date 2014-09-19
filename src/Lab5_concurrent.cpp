//============================================================================
// Name        : Lab5_concurrent.cpp
// Author      : Amila
// Version     :
// Copyright   : This is for Academic purposes
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include <vector>
#include <omp.h>
using namespace std;

void initArrays(int n, double*& a, double*& b, double*& c);
double multiplyMatrix(int n, double*& a, double*& b, double*& c);
double p_multiplyMatrix(int n, double*& a, double*& b, double*& c);
double p_cache_op_multiplyMatrix(int n, double*& a, double*& b, double*& c);
double parallelRunCacheOptimized(int n);
void cleanUp(double*& a, double*& b, double*& c);
double fRand();
double sequentialRun(int n);
double parallelRun(int n);
int main(int args, char* arg[]) {
	int n = atoi(arg[2]);
	int p = atoi(arg[1]);
	if (p == 0) {
		double t = sequentialRun(n);
		cout << t << endl;
	} else if (p == 1) {
		double t = parallelRun(n);
		cout << t << endl;
	} else if (p == 2) {
		double t = parallelRunCacheOptimized(n);
		cout << t << endl;
	}
	return 0;
}
double sequentialRun(int n) {
	srand(time(NULL));
	double* a, *b, *c;
	initArrays(n, a, b, c);
	double temp = multiplyMatrix(n, a, b, c);
	return temp;
}
double parallelRun(int n) {
	srand(time(NULL));
	double* a, *b, *c;
	initArrays(n, a, b, c);
	double temp = p_multiplyMatrix(n, a, b, c);
	return temp;
}
double parallelRunCacheOptimized(int n) {
	srand(time(NULL));
	double* a, *b, *c;
	initArrays(n, a, b, c);
	double temp = p_cache_op_multiplyMatrix(n, a, b, c);
	return temp;
}
void initArrays(int n, double*& a, double*& b, double*& c) {
	int i, j;
	a = (double*) malloc(n * n * sizeof(double)); //new double[n*n];
	b = (double*) malloc(n * n * sizeof(double));
	c = (double*) malloc(n * n * sizeof(double));
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			a[n * i + j] = fRand();
			b[n * i + j] = fRand();
			c[n * i + j] = 0.0;
		}
	}
}
void cleanUp(double*& a, double*& b, double*& c) {
	free(a);
	free(b);
	free(c);
}
double multiplyMatrix(int n, double*& a, double*& b, double*& c) {
	int i, j, k;
	double timeStart = omp_get_wtime();
	double temp = 0.0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			for (k = 0; k < n; k++) {
				temp = temp + a[n * i + k] * b[n * k + j];
			}
			c[n * i + j] = temp;
			temp = 0;
		}
	}
	double timeEnd = omp_get_wtime();
	return timeEnd - timeStart;
}
double p_multiplyMatrix(int n, double*& a, double*& b, double*& c) {
	double timeStart = omp_get_wtime();
#pragma omp parallel for
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			double temp = 0.0;
			for (int k = 0; k < n; k++) {
				temp = temp + a[n * i + k] * b[n * k + j];
			}
			c[n * i + j] = temp;
			temp = 0;
		}
	}
	double timeEnd = omp_get_wtime();
	return timeEnd - timeStart;
}
double p_cache_op_multiplyMatrix(int n, double*& a, double*& b, double*& c) {
	double timeStart = omp_get_wtime();
#pragma omp parallel for
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < n; k++) {
			for (int j = 0; j < n; j++) {
				c[n * i + j] = c[n * i + j] + a[n * i + k] * b[n * k + j];
			}
		}
	}
	double timeEnd = omp_get_wtime();
	return timeEnd - timeStart;
}
double fRand() {
	double f = (double) random() / RAND_MAX;
	return f * 11.0;
}
