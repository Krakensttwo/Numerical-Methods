/*
Task 2: Implement the bisection method for finding roots in C++.

Compilation: g++ bisect.cpp -lm
Example invocation: ./a.out sin -1.0 2.0 0.1 0.01 100

This command calculates the approximate root, approximation error, the value of the function at the found root, and the number of algorithm steps for the sine function on the interval [-1.0, 2.0] with a precision of delta=0.1, epsilon=0.01, and a maximum of 100 iterations.
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
	double a, b, delta, epsilon, yc, c, err;
	int max, k;
	double ya, yb;
	string f;

	if (argc!=7) {
		cout << "Invalid number of arguments.\n";
		return -1;
	}
	f=argv[1];
	a=stod(argv[2]);
	b=stod(argv[3]);
	delta=stod(argv[4]);
	epsilon=stod(argv[5]);
	max=atoi(argv[6]);
	ya = feval(f,a);
	yb = feval(f,b);
	
	if (ya*yb > 0) {
		return -1;
	}
	
	for(k=1;k<=max;k++) {
		c=a+(b-a)/2.0;
		yc=feval(f,c);
		err=abs((b-a)/2.0);
		if(err<delta || abs(yc)<epsilon) {
			cout << "c = " << c << "\nerr = " << err << "\nyc = " << yc << "\nk = " << k << endl;
			return 0;
		}
		if(yb*yc>0) {
			b=c;
			yb=yc;
		} else {
			a=c;
		}
	}
}

