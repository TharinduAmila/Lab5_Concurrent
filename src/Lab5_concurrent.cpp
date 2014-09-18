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
using namespace std;

void initArrays(double n,vector<vector<double> > &a,vector<vector<double> > &b,vector<vector<double> > &c);
void multiplyMatrix(double n,vector<vector<double> > a,vector<vector<double> > b,vector<vector<double> > &c);
double fRand();
void sequentialRun(double n);
int main() {
	sequentialRun(2);
	return 0;
}
void sequentialRun(double n){
	srand(time(NULL));
	double i, j;
	vector<vector<double> > a,b,c;
    initArrays(n,a,b,c);
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
		multiplyMatrix(n,a,b,c);
		cout << "\n-----------------------------------------------------------\n";

		cout << "\n\nMultiplication of Matrix A and Matrix B :\n\n";
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				cout << "\t" << c[i][j];
			}
			cout << "\n\n";
		}
}
void initArrays(double n,vector<vector<double> > &a,vector<vector<double> > &b,vector<vector<double> > &c) {
	cout << "Init Called" << endl;
	int i,j;
	for (i = 0; i < n; i++) {
		vector<double> temp,temp1,temp2;
			for (j = 0; j < n; j++) {
				temp.push_back(fRand());
				temp1.push_back(fRand());
				temp2.push_back(0.0);
			}
			a.push_back(temp);
			b.push_back(temp1);
			c.push_back(temp2);
		}
}

void multiplyMatrix(double n,vector<vector<double> > a,vector<vector<double> > b,vector<vector<double> > &c) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				c[i][j] = c[i][j] + a[i][k] * b[k][j];
			}
		}
	}
}
double fRand() {
	double f = (double) random() / RAND_MAX;
	return f*11.0;
}
