/*
Compilation: g++ wdmn4.cpp
Example invocation: ./a.out  1.0  1.0  0.0  0.0  -4.0  2.0  1.0  -3.0  0.001 100
*/
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <complex>
#include <math.h>
using namespace std;

struct yz {
  complex<double> y;
  complex<double> z;
} dh;

yz dhorner(vector<complex<double>> W, complex<double> x) {
	yz result;
	int n=W.size();
    result.y=W[0];
    result.z=0;
	for(int i=1;i<n;i++) {
        result.z=result.y+result.z*x;
        result.y=result.y*x+W[i];
    }
	return result;
}

int main(int argc, char *argv[]) {
	
	vector<complex<double>> W;
	complex<double> p0, pn, temp;
	double err, delta;
	int max, n;
	
	if(argc<7) {
		cout << "Invalid number of arguments.\n";
		return -1;
	}
	p0.real(stod(argv[argc-4]));
	p0.imag(stod(argv[argc-3]));
	delta=stod(argv[argc-2]);
	max=atoi(argv[argc-1]);
	//cout << p0.real() << " " << p0.imag() << " " <<   delta    << " " <<  max << endl;
	n=argc-5;
	if(n%2) {
		cout << "Odd number of arguments.\n";
		return -1;
	}
	
	for(int i=1;i<n;i=i+2) {
		temp.real(stod(argv[i]));
		temp.imag(stod(argv[i+1]));
		W.push_back(temp);
	}
	
	for(int k=1;k<=max;k++) {
		dh=dhorner(W, p0);
		pn=p0-(dh.y/dh.z);
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


