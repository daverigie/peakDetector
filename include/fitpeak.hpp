#ifndef UTIL_H
#define UTIL_H

#include <complex>
#include <cmath>
#include <stdlib.h>
#include "array2d.hpp"
#include "util.hpp"
#include <omp.h>
#include "brent.hpp"

using namespace std;

const double PI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208;
const double GOLDEN_RATIO = (sqrt(5.0) + 1.0)/2.0;

template <class T>
struct costfun 
{
	const complex<T> *  yy;
    size_t N;
	const T operator()(T f0){
			
		complex<T> val = (0.0, 0.0);
		complex<T> _i_(0,1);
		T dt = 0.5;

		for (int i=0; i<N; i++){
			T t = dt*((T)i);
			val += conj(yy[i])*exp(_i_*2.0*PI*f0*t);
		}

		return -abs(val);
	}
};

class costfun_brent : public brent::func_base
{
	public: 
		const complex<double> *  yy;
		size_t N;
		double operator()(double f0){
				
			complex<double> val = (0.0, 0.0);
			complex<double> _i_(0,1);
			double dt = 0.5;

			for (int i=0; i<N; i++){
				double t = dt*((double)i);
				val += conj(yy[i])*exp(_i_*2.0*PI*f0*t);
			}

			return -abs(val);
		}
};

template <class T>
class FFT
{
	private: 
		Array2d<complex<T>> F;
		size_t N;
		
	public:
		FFT(size_t N);
		T time(int i) const;
		T freq(int i) const;
		void transform(const complex<T>* y, complex<T>* yft) const;
};

template <class T>
FFT<T>::FFT(size_t N) : F(N, N) {

	this->N = N;

	complex<T> _i_(0,-1);

	for (int i=0; i<N; i++){
		for (int j=0; j<N; j++){
			F(i,j) = exp(_i_*2.0*PI*freq(i)*time(j));
		}
	}
}

template <class T>
T FFT<T>::time(int i) const{
	T dt = 0.5;
	return ((T)i)*dt;
}

template <class T>
T FFT<T>::freq(int i) const{
	T df = 2.0/((T)N);
	T center = (int)((T)N/2.0);
	return df*((T)i - center);
}


template <class T>
void FFT<T>::transform(const complex<T>* y, complex<T>* yft) const{

	for (int i=0; i<N; i++){
		yft[i] = complex<T>(0.0,0.0);
		for (int j=0; j<N; j++){
			yft[i] += F.at(i,j)*y[j];
		}
	}
}

template <class T>
double gs_search(T& f, double a, double b, double tol){

	double c, d, xopt;
	double fval;

	c = b - (b - a) / GOLDEN_RATIO;
	d = a + (b - a) / GOLDEN_RATIO;
	double err = abs(c-d);

	int iter = 0;

	while (err > tol){
		if ( f(c) < f(d) ){
			b = d;
		}
		else{
			a = c;
		}

		c = b - (b - a) / GOLDEN_RATIO;
		d = a + (b - a) / GOLDEN_RATIO;

		xopt = (b + a) / 2.0;
		fval = f(xopt);
		err = abs(c-d);
		iter += 1;		
	}

	return xopt;
}

template <class T>
T fit_sinusoid(const complex<T> * yy, complex<T> * yyft, FFT<T> & fft, T fmin, T fmax, T ftol, size_t N){

	T fopt = fmin;
	//struct costfun<T> fun;
	costfun_brent fun;
	fun.yy = yy;
    
	fun.N  = N;
	T dt = 0.5;
	T df = 1.0/((T)N*dt);	

	fft.transform(yy, yyft);

	fopt   = fmin;
	T f    = fmin;
	T fval = 0; 
	
	
	for (int i=0; i<N; i++){
		if ( (fft.freq(i) >= fmin) && (fft.freq(i) <= fmax) ){
			if (abs(yyft[i]) > fval){
				fval = abs(yyft[i]);
				fopt = fft.freq(i);
			}
		}
	}
	
	fmin = fopt - df;
	fmax = fopt + df;

	//fopt = gs_search<struct costfun<T>>(fun, fmin ,fmax, ftol);
	fval = brent::local_min(fmin, fmax, ftol, fun, fopt);

    return fopt;
}

template <class T>
Array2d<T> fit_all_sinsoids(Array2d<complex<T>>&  kdata, T* fmin_arr, T* fmax_arr, T ftol){

	size_t M = kdata.size(0);
    size_t N = kdata.size(1);

	int MAX_THREADS = omp_get_max_threads(); 
	
	FFT<T> fft(N);

	complex<T> * yyft = new complex<T>[MAX_THREADS*N];

	Array2d<T> fopt_arr(M,1);

	#pragma omp parallel for 
	for (int i=0; i<fopt_arr.numel(); i++){
		int tid = omp_get_thread_num();
		fopt_arr[i] = fit_sinusoid(kdata.extract(i), &yyft[N*tid], fft, fmin_arr[i], fmax_arr[i], ftol, N);
	}

	delete [] yyft;

    return fopt_arr;
}

#endif