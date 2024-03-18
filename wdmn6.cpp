/*
Compilation: g++ wdmn6.cpp
Example invocation:
./a.out  1.0  3.0 2.0 4.1 2.0 2.0 1.0 3.0 4.0 -1.0 2.0 -2.0 1.2 2.1 3.1 7.0
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
	
	void eye(int dim) {
		vector<double> row;
		for(int i=0;i<dim;i++) {
			for(int j=0;j<dim;j++) {
				if(i==j) {
					row.push_back(1.0);
				} else {
					row.push_back(0.0);
				}
			}
			a.push_back(row);
			row.clear();
		}
	}
	
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
	
	vector<double> max() {
		vector<double> s;
		double m;
		for(int i=0;i<a.size();i++) {
			m=abs(a[i][0]);
			for(int j=1;j<a.size();j++) {
				if(abs(a[i][j])>m) {
					m=abs(a[i][j]);
				}
			}
			s.push_back(m);
		}	
		return s;
	}
	
	int main_row_index(int k, int n, vector<int> p, vector<double> s) {
		int row_index=0;
		double max=0;
		for(int i=k;i<n;i++) {
			if(max<abs(a[p[i]][k])/(s[p[i]])) {
				max=abs(a[p[i]][k])/(s[p[i]]);
				row_index=p[i];
			}
		}
		return row_index;
	}
	
	void swap_rows(vector<int> p) {
		vector<vector<double>> temp;
		for(int i=0;i<p.size();i++) {
			temp.push_back(a[p[i]]);
		}
		a=temp;
	}
};


int main(int argc, char *argv[]) {
	matrix A,P,L,U;
	vector<double> elements, s;
	vector<int> p;
	int n,r;
	double t,z;
	
	n=(int)sqrt(argc-1);
	if(n!=sqrt(argc-1) || n==0) { 
		cout << "Invalid number of arguments.\n" << endl;
		return -1;
	}
	for(int i=1;i<argc;i++) {
		elements.push_back(stod(argv[i]));
	}
	A.fill(elements, n);
	L.eye(n);
    P.eye(n);
    U.zeros(n);
	for(int i=0;i<n;i++) {
		p.push_back(i);
	}
	s=A.max();
	for(int k=0;k<n-1;k++) {
		int j=A.main_row_index(k,n,p,s);
		j=j+k;
        t=p[j];
        p[j]=p[k];
        p[k]=t;
		for(int i=k+1;i<n;i++) {
			z=A.a[p[i]][k]/A.a[p[k]][k];
            A.a[p[i]][k]=z;
			for(int r=k+1;r<n;r++) {
				A.a[p[i]][r]=A.a[p[i]][r]-(z*A.a[p[k]][r]);
			}
		}
	}
    P.swap_rows(p);
    A.swap_rows(p);
    for(int i=0;i<n;i++) {
        for(int j=0;j< n;j++) {
            if(i<=j) {
                U.a[i][j] = A.a[i][j];
			} else {
				L.a[i][j] = A.a[i][j];
			}
		}
	}
	cout << "matrix P" << endl;
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			cout << P.a[i][j] << " ";
		}
		cout << endl;
	}
	cout << "matrix L" << endl;
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			cout << L.a[i][j] << " ";
		}
		cout << endl;
	}
	cout << "matrix U" << endl;
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			cout << U.a[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	return 0;
}


