/*
Task 5: Implement the Laguerre's method for finding roots of a polynomial in C++. The program should find complex roots for polynomials with complex coefficients.

Compilation: g++ laguerre.cpp
Example invocation: ./a.out  1.0  1.0  0.0  0.0  -4.0  2.0  1.0  -3.0  0.001 100

This command means that we are computing the root for the polynomial 
W(x) = (1+i)x^2 + (-4+2i), 
starting from the point 1-3i.
(delta=0.001 and max=100)
*/
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <vector>
#include <complex> // Complex numbers along with overloaded operators.

using namespace std;

// store the result of ddhorner()
struct yzv {
  complex<double> y;
  complex<double> z;
  complex<double> v;
} ddh;

yzv ddhorner(vector<complex<double>> W, complex<double> x) {
	yzv result;
	int n=W.size();
    result.y=W[0];
    result.z=0;
	for(int i=1;i<n;i++) {
		result.v=result.z+result.v*x;
        result.z=result.y+result.z*x;
        result.y=result.y*x+W[i];
    }
	result.v=2.0*result.v;
	return result;
}
void displayError(int error);
void displayComplex(complex<double> x, int precision);


int main(int argc, char *argv[]) {
	
	vector<complex<double>> W;
	complex<double> p0, pn, temp;
	double err, delta;
	int max,m;

	complex<double> a,b,c,c1,t;
	double n;
	
	if(argc<7) {
		cout << "Invalid number of arguments.\n";
		return -1;
	}
	
	p0.real(stod(argv[argc-4]));
	p0.imag(stod(argv[argc-3]));
	delta = stod(argv[argc-2]);
	max = atoi(argv[argc-1]);
	
	// The number of arguments describing coefficients must be even.
	m=argc-5;
	if(m%2) {
		cout << "Odd number of arguments.\n";
		return -1;
	}
	
	for(int i=1;i<m;i=i+2) {
		temp.real(stod(argv[i]));
		temp.imag(stod(argv[i+1]));
		W.push_back(temp);
	}

	n=W.size()-1;
	for(int k=1;k<=max;k++) {
		ddh=ddhorner(W,p0);
		if(ddh.y==0.0) {
			err=0;
			pn=p0;
			return 1;
		}
		
		a=-ddh.z/ddh.y;
		b=(a*a)-(ddh.v/ddh.y);
		t=sqrt((n-1)*(n*b-a*a));
		c1=(a+t)/n;
		c=(a-t)/n;
		
		if(abs(c1)>abs(c)) {
			c=c1;
		}
		pn=p0+(1.0/c);
		err=abs(pn-p0);
		p0=pn;
		if(err<delta) {
			cout << "pn = "<< p0.real() << " " << p0.imag() << "i" << endl;
			cout << "err = " << err << endl;
			cout << "k = " << k << endl;
			return 0;
		}
	}
	cout << "Maximum loop iterations reached." << endl;
	return 1;
}

