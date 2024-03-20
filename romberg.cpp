/*
Task 13: Implement Romberg's method for numerical integration in C++.

Compilation: g++ romberg.cpp
Przykładowe wywołanie programu:
./a.out sin -1.0 2.4 8

This command will compute an array of successive approximations of the integral of sin(x) over the interval [-1, 2.4] using Romberg's method with 8 steps.
*/
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
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

double sum(string f, double a, double n, double h) {
	double sum=0;
	double p=1;
	
	for(int i=0;i<n-1;i++) {
		p=p*2;
	}
	//cout << p << endl;
	for(int i=1;i<=p;i++) {
		sum=sum+feval(f,(a+(2*i-1)*h));
	}
	//cout << sum << endl;
	return sum;
}

int main(int argc, char *argv[]) {
	matrix R;
	int n, M;
	double a, b, h;
	string f;
	
	if(argc!=5) { 
		cout << "Incorrect number of arguments" << endl;
		return -1;
	}
	
	if(stod(argv[2])>=stod(argv[3])) {
		cout << "Incorrect arguments" << endl;
		return -1;
	}
	f=argv[1];
	a=stod(argv[2]);
	b=stod(argv[3]);
	M=stoi(argv[4]);
	h=b-a;	
	R.zeros(M+1);
	for(n=1;n<=M;n++) {
		h=h/2;
		R.a[n][0]=0.5*R.a[n-1][0]+h*sum(f,a,n,h);
		for(int m=1;m<=n;m++) {
			int mm=1;
			for(int i=1;i<=m;i++) {
				mm=mm*4;
			}
			R.a[n][m]=R.a[n][m-1]+(R.a[n][m-1]-R.a[n-1][m-1])/(mm-1);
		}
	}
	
	cout << endl << "R = " << endl;
	for(int i=0;i<M+1;i++) {
		for(int j=0;j<n;j++) {
			cout << R.a[i][j] << " ";
		}
		cout << endl;
	}
	
	return 0;
}


