//#include <matrix.h>
#include "array2d.hpp"
#include <complex>
#include "fitpeak.hpp"
#include "mexutils.hpp"
#include "mex.h"

Array2d<std::complex<double>> mexArrayToArray2d(const mxArray *m_arr);
mxArray * array2dToMexArray(Array2d<double> &arr);

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{

    double *fmin_arr = mxGetPr(prhs[1]);
    double *fmax_arr = mxGetPr(prhs[2]);
    double *ftol_arr = mxGetPr(prhs[3]);
    double ftol      = ftol_arr[0];

    Array2d<std::complex<double>> arr = mexArrayToArray2d(prhs[0]);

    Array2d<double> result = fit_all_sinsoids<double>(arr, fmin_arr, fmax_arr, ftol);

    plhs[0] = array2dToMexArray(result);

}

Array2d<std::complex<double>> mexArrayToArray2d(const mxArray *m_arr){

    size_t numElems     = mxGetNumberOfElements(m_arr);
    const int *mx_dims  = mxGetDimensions(m_arr);

    size_t numCols   = mx_dims[0];
    size_t numRows   = numElems/numCols;

    Array2d<std::complex<double>> arr = form_complex_array<double>( mxGetPr(m_arr), mxGetPi(m_arr), numRows, numCols);

    return arr;

}

 mxArray* array2dToMexArray(Array2d<double> &arr){

    mxArray *m_arr      = mxCreateDoubleMatrix(arr.size(1), arr.size(0), mxREAL);
    size_t numElems     = mxGetNumberOfElements(m_arr);
    double * m_arr_data = mxGetPr(m_arr);

    
    for (int i=0; i<numElems; i++){
        m_arr_data[i] = arr.at(i);
    }  
    

    return m_arr;
}