/*
Compilation: g++ wdmn7.cpp
Example invocation:
./a.out  2.0  -0.5 0.1 4.0 -7.0 -1.0 1.0 2.0 4.0 1.0 2.0 3.0 1.0 -3.0 2.0 0.001 100
*/

#include <iostream>
#include <string>
#include <math.h>
#include <vector>
using namespace std;

class matrix {
	public: 
	vector<vector<double>> a;
	void fill(vector<double> m, int dim) {
		vector<double> row;
		for(int i=0;i<dim;i++) {
			for(int j=0;j<dim;j++) {
				row.push_back(m[i*dim + j]);
			}
			a.push_back(row);
			row.clear();
		}
	}
};

int main(int argc, char *argv[]) {
	matrix A;
	vector<double> elements, B, X0, XN, temp1;
	int m=3,p=5,t=1,n=1, b=1,x,k,max;
	double err, d, delta, temp, norm;
	
	for(int i=1;m<=argc-3;p=p+2) {
		if(m==argc-3) {
			t=0;
			break;
		}
		m=m+p;
		n++;
	}
	if(t==1) {
	cout << "Invalid number of arguments.\n" << endl;
		return -1;
	}
	for(int i=1;i<=n*n;i++) {
		//cout << argv[i] << endl;
		elements.push_back(stod(argv[i]));
		b++;
	}
	x=b;
	for(int i=b;i<=n*n+n;i++) {
		B.push_back(stod(argv[i]));
		x++;
	}
	for(int i=x;i<=argc-3;i++) {
		X0.push_back(stod(argv[i]));
	}
	A.fill(elements, n);
	delta=stod(argv[argc-2]);
	max=atoi(argv[argc-1]);
	/*
	cout << "matrix A" << endl;
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			cout << A.a[i][j] << " ";
		}
		cout << endl;
	}
	cout << "matrix B" << endl;
	for(int i=0; i< B.size();i++) {
		cout << B[i] << " ";
	}
	cout << endl;
	cout << "matrix X0" << endl;
	for(int i=0; i< X0.size();i++) {
		cout << X0[i] << " ";
	}
	cout << endl;
	*/
	
	for(int i=0; i<n;i++) {
		XN.push_back(0);
		temp1.push_back(0);
	}
	for(int i=0; i<n;i++) {
		d= 1/A.a[i][i];
		B[i]=d*B[i];
		for(int j=0; j<n; j++) {
			A.a[i][j]=d*A.a[i][j];
		}
	}
	
	for(k=1; k<max; k++) {
		for(int i=0; i<n; i++) {
			temp=0;
			for(int j=0; j<n; j++) {
				if(j!=i) {
					temp=temp+A.a[i][j] *X0[j];
				}
			}
			XN[i]=B[i]-temp;
		}
		for(int i=0;i<n;i++) {
			temp1[i]=XN[i]-X0[i];
		}
		norm=0;
		for(int i=0;i<n;i++) {
			norm=norm+temp1[i]*temp1[i];
		}
		err=sqrt(norm);
		X0=XN;
		if(err < delta) {
			break;
		}
	}
	cout << "err=" << err << " k=" << k << endl;
	cout << "Matrix XN" << endl;
	for(int i=0; i< XN.size();i++) {
		cout << XN[i] << endl;
	}
	cout << endl;

	return 0;
}