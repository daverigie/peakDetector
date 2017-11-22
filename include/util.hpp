#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <complex>
#include <cmath>
#include <stdlib.h>
#include <vector>
#include <math.h>

using namespace std;


template <class T>
complex<T> crand(){
	complex<T> val(((T) rand() / (RAND_MAX)) , ((T) rand() / (RAND_MAX)));
	return val;
}

template <class T>
vector<complex<T>> randvec(int N){
	vector<complex<T>> xx(N);
	for (int i=0; i<N; i++){
		xx[i] = crand<T>();
	}

	return xx;
}

template <class T>
void printarray(vector<T>& arr){
	cout << "[";
	for (int i=0; i<arr.size()-1; i++){
		cout << arr[i];
		cout << ", ";
	}
	cout << arr[arr.size()-1];
	cout << "]";

}


#endif