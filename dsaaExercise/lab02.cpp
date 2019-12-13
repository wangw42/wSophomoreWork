/*
Lab Work 02-1. Comparisons of Different Complexity Classes

Note. Programming in C++, including <iostream>/<iostream.h> and <cmath>/<math.h> only

Let n be a positive integer with specified initial value.

Design and implement a C++ program to find the least number N such that g(n)>=f(n) when n>N.

1. n=1, f(n)=n and g(n)=nln(n)
2. n=1, f(n)=n^10 and g(n)=2^n
3. n=2, f(n)=n^10 and g(n)=n!
4. n=2, f(n)=10^n and g(n)=n!
(END)

*/


#include <iostream>
#include <cmath>

using namespace std;

long long fact(int );
long double logfact(int);

int main(){
	int n1 = 1, n2 = 1, n3 = 2, n4 = 2;
	
	for(int i = 1;; i++){
		if(i <= i*log(i)) {
			n1 = i;
			break;
		}
	}
	
	
	
	for(int i = 2;; i++){
		if(pow(i,10) <= pow(2,i)){
			n2 = i;
			break;
		}
	}
	
	
	for(int i = 2;; i++){
		if(pow(i,10) <= fact(i)){
			n3 = i;
			break;
		}
	}
	
	for(int i = 2;; i++){
		if(i*log(10)<= logfact(i)){
			n4 = i;
			break;
		}
	}
	
	cout << "(1) " << n1 << endl;
	cout << "(2) " << n2 << endl;
	cout << "(3) " << n3 << endl;
	cout << "(4) " << n4 << endl;
	
	return 0;
}

long long fact(int n ){
	long long res = 1;
	for(int i = 1; i <= n; i++){
		res *= i;
	}
	return res;
};


long double logfact(int n){
	long double res = 0;
	for(int i = 1; i <= n; i++){
		res += log(i);
	}
	return res;
};
