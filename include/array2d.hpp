#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <complex>
#include <iostream>

using namespace std;

template <class T>
class Array2d {

    private:
        T * data = NULL;
        size_t dims[3];
    public:
        Array2d(const Array2d<T> & obj);
        Array2d(size_t num_rows, size_t num_cols);
        Array2d(T* arr_data, size_t* dims);
        Array2d(T* data_in, size_t num_rows, size_t num_cols);
        size_t size(int dim) const;
        size_t numel() const;
        T at(int idx) const;
        T at(int i, int j) const;
        T& operator[](int idx);
        T& operator()(int i, int j);
        int sub2ind(int i, int j) const;
        T * extract(int i) const;
        ~Array2d();

};


template <class T>
Array2d<T>::Array2d(const Array2d<T> & obj){
    
    dims[0] = obj.dims[0];
    dims[1] = obj.dims[1];

    obj.numel();

    for (int i=0; i< obj.numel(); i++){
        data[i] = obj.at(i);
    }
    
}


template <class T>
Array2d<T>::Array2d(size_t num_rows, size_t num_cols){
    data = new T[num_rows*num_cols];
    dims[0] = num_rows; dims[1] = num_cols; 

    for (int i=0; i<num_rows*num_cols; i++){
        data[i] = 0.0;
    }
}

template <class T>
Array2d<T>::Array2d(T* data_in, size_t num_rows, size_t num_cols){
    data = new T[num_rows*num_cols];
    dims[0] = num_rows; dims[1] = num_cols;

    for (int i=0; i<num_rows*num_cols; i++){
        data[i] = data_in[i];
    }
}

template <class T>
size_t Array2d<T>::size(int dim) const{
    return dims[dim];
}

template <class T>
size_t Array2d<T>::numel() const{
    return dims[0]*dims[1];
}

template <class T>
T Array2d<T>::at(int idx) const{
    return data[idx];
}

template <class T>
T Array2d<T>::at(int i, int j) const{
    return data[sub2ind(i,j)];
}

template <class T>
T& Array2d<T>::operator[](int idx){
    return data[idx];
}

template <class T>
T& Array2d<T>::operator()(int i, int j){
    return data[sub2ind(i,j)];
}

template <class T>
int Array2d<T>::sub2ind(int i, int j) const{
    return i*((int)dims[1]) + j;
}


template <class T>
T * Array2d<T>::extract(int i) const{
    T * vec = &(data[sub2ind(i,0)]);
    return vec;
}

template <class T>
Array2d<T>::~Array2d(){
    delete [] data;
}

template <class T>
void printarray2d(Array2d<T>&  arr){
    
        for (int i=0; i<arr.size(0); i++){
            cout << "\n";
            for (int j=0; j<arr.size(1); j++){
                cout << arr(i,j);
                cout << " ";
            }
        }
        cout << "\n";
}

template <class T>
Array2d<complex<T>> form_complex_array(T* real_data, T* imag_data, size_t num_rows, size_t num_cols){


    Array2d<complex<double>> X(num_rows, num_cols);

    for (int i=0; i<num_rows*num_cols; i++){
        X[i] = complex<T>(real_data[i], imag_data[i]);
    }

    return X;

}

#endif 