/*
Compilation: g++ wdmn11.cpp
Example program invocation:
./a.out sin 2.0 0.1 8
*/
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
using namespace std;

class matrix {
	public: 
	vector<vector<double>> a;
	
	void zeros(int dim) {
		vector<double> row;
		for(int i=0;i<dim;i++) {
			for(int j=0;j<dim;j++) {
				row.push_back(0.0);
			}
			a.push_back(row);
			row.clear();
		}
	}
};

double feval(string function,double argument){
	if(function=="sin") {
		return sin(argument);
	}
	if(function=="cos") {
		return cos(argument);
	}
	if(function=="tan") {
		return tan(argument);
	}
	if(function=="exp") {
		return exp(argument);
	}
	if(function=="log") {
		return log(argument);
	}
	if(function=="sqrt") {
		return sqrt(argument);
	}
	return -1;	
}

int main(int argc, char *argv[]) {
	matrix D;
	int M;
	string f;
	double a, h, dh;
	if(argc!=5 || !stod(argv[3])) { 
		cout << "Incorrect number of arguments" << endl;
		return -1;
	}
	f=argv[1];
	a=stod(argv[2]);
	h=stod(argv[3]);
	M=stoi(argv[4]);
	D.zeros(M+1);
	for(int n=0;n<=M;n++) {
		int nn=1;
		for(int i=0;i<n;i++) {
			nn=nn*2;
		}
		dh=h/(nn);
		D.a[n][0]=(feval(f,(a+dh))-feval(f,(a-dh)))/(2*dh);
	}
	for(int k=1;k<=M;k++) {
		for(int n=k;n<=M;n++) {
			int kk=1;
			for(int i=1;i<=k;i++) {
				kk=kk*4;
			}
			D.a[n][k]=D.a[n][k-1]+(D.a[n][k-1]-D.a[n][k-1])/(kk-1);
		}
	}
	cout << endl << "D = " << endl;
	for(int i=0;i<M+1;i++) {
		for(int j=0;j<M+1;j++) {
			cout << D.a[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}


