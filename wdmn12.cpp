/*
Compilation: g++ wdmn11.cpp
Example program invocation:
./a.out sin -1.0 2.4  8
*/
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

double sum(vector<double> v) {
	int i;
	double s=0;
	for(int i=0;i<v.size();i++) {
		s=s+v[i];
	}
	return s;
}

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
	vector<double> x,y;
	int M;
	double a, b, h, s, s1, s2;
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
	h=(b-a)/(2*M);
	for(double i=a+h;i<=b-h;i=i+2*h) {
		//cout << "x4,5 "<< i  << endl;
		x.push_back(i);
		y.push_back(feval(f,i));
	}
    s1=sum(y);
	x.clear();
	y.clear();
	for(double i=a+2*h;i<=b-2*h;i=i+2*h) {
		x.push_back(i);
		y.push_back(feval(f,i));
	}
    s2=sum(y);
    s=h*(feval(f,a)+feval(f,b)+4*s1+2*s2)/3;
	cout << "s = " << s << endl;
	return 0;
}


