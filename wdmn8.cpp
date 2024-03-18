/*
Compilation: g++ wdmn8.cpp
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

vector<double> div(vector<double> v, double x) {
	for(unsigned int i=0;i<v.size();i++) {
		v[i]=v[i]/x;
	}
	return v;
}

int main(int argc, char *argv[]) {
	matrix L;
	vector<double> X, Y, V, C;
	int w, n;
	double temp=0;
	
	if((argc-1)%2!=0) { 
		cout << "Invalid number of arguments.\n" << endl;
		return -1;
	}

	w=(argc-1)/2;
	n=w-1;

	for(int i=1;i<argc;i++) {
		if(i<=w) {
			X.push_back(stod(argv[i]));
		} else {
			Y.push_back(stod(argv[i]));
		}
	}
	L.zeros(w);
	for(int k=0;k<n+1;k++) {
		V.clear();
        V.push_back(1);
		for(int j=0;j<n+1;j++) {
            if(k!=j) {
                V=div(conv(V, poly(X[j])), X[k]-X[j]);
			}
		}
        L.a[k]=V;
	}
	
	for(int i=0;i<w;i++) {
		for(int j=0;j<w;j++) {
			temp=temp+Y[j]*L.a[j][i];
		}
		C.push_back(temp);
		temp=0;
	}	
	cout << "C = " << endl;
	for(int i=0;i<w;i++) {
		cout << C[i] << " ";
	}
	cout << endl << "L = ";
	for(int i=0;i<w;i++) {
		for(int j=0;j<w;j++) {
			cout << L.a[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}
