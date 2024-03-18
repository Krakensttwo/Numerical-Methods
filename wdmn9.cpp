/*
Compilation: g++ wdmn9.cpp
Example program invocation:
./a.out  -1.0 0.0 2.0 3.0 -7.2 2.0 -11.1 2.0
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

vector<double> conv(vector<double> u, vector<double> v) {
	vector<double> w;
	int m, n, s, j;
	m=u.size();
	n=v.size();
	s=m+n-1;
	w.resize(s, 0);
	u.resize(s, 0);
	v.resize(s, 0);
	for(int i=0;i<s;i++) {
		for(int j=0;j<=i;j++) {
			w[i]=w[i]+u[j]*v[i-j];
		}
	}
	return w;
}

vector<double> poly(double x) {
	return {1, -x};
}

int main(int argc, char *argv[]) {
	matrix D;
	vector<double> X, Y, C;
	int m, n;
	
	if((argc-1)%2!=0) { 
		cout << "Incorrect number of arguments" << endl;
		return -1;
	}

	n=(argc-1)/2;

	for(int i=1;i<argc;i++) {
		if(i<=n) {
			X.push_back(stod(argv[i]));
		} else {
			Y.push_back(stod(argv[i]));
		}
	}
	
	D.zeros(n);
	for(int i=0;i<n;i++) {
		D.a[i][0]=Y[i];
	}
	for(int j=1;j<n;j++) {
		for(int k=j;k<n;k++) {
			D.a[k][j]=(D.a[k][j-1]-D.a[k-1][j-1])/(X[k] - X[k-j]);
		}
	}
	C.push_back(D.a[n-1][n-1]);
    for(int k=n-2;k>=0;k--) {
		C=conv(C, poly(X[k]));
        m=C.size()-1;
        C[m]=C[m]+D.a[k][k];
	}
	
	cout << "C = " << endl;
	for(int i=0;i<(int)C.size();i++) {
		cout << C[i] << " ";
	}
	
	cout << endl << "D = ";
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			cout << D.a[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}


