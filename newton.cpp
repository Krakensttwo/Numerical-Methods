/*
Task 3: Implement the secant method for finding roots in C++.

Compilation: g++ newton.cpp -lm
Example invocation: ./a.out sin -1.2 -1.0 0.001 0.001 100

This command finds one of the roots of the sine function, starting from points -1.2 and -1.0, with a result accuracy of delta=0.001, epsilon=0.001, and a maximum of 100 iterations. The program works with real numbers.
*/
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

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
	string f;
	double p0, p1, delta, epsilon;
	int max, k;
	double pn, ypn, err;
	
	if (argc!=7) {
		cout << "Invalid number of arguments.\n";
		return -1;
	}
	f=argv[1];
	p0=stod(argv[2]);
	p1=stod(argv[3]);
	delta=stod(argv[4]);
	epsilon=stod(argv[5]);
	max=atoi(argv[6]);
	
	for(k=1;k<=max;k++) {
        pn=p1-feval(f,p1)*(p1-p0)/(feval(f,p1)-feval(f,p0));
        err=abs(pn-p1);
        p0=p1;
        p1=pn;
        ypn=feval(f,pn);
		if(err<delta || abs(ypn)<epsilon) {
			cout << "pn = " << pn << "\nerr = " << err << "\nypn = " << ypn << "\nk = " << k << endl;
			return 0;
		}
	}
}

