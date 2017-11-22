//#include <matrix.h>
#include "array2d.hpp"
#include <complex>
#include "main.hpp"
#include "mexutils.hpp"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{

    mxstreambuf mout;

    double *p    = mxGetPr(prhs[0]);
    int dims[2] = {1, 1};
    const int mx_num_dims = mxGetNumberOfDimensions(prhs[0]);
    const int *mx_dims = mxGetDimensions(prhs[0]); 

    
    for (int i=0; i<mx_num_dims; i++){
        dims[i] = mx_dims[i];
    }

    Array2d<std::complex<double>> arr = form_complex_array<double>( mxGetPr(prhs[0]), mxGetPi(prhs[0]), dims[1], dims[0]);

    Array2d<double> result = fit_all_sinsoids<double>(arr, mxGetPr(prhs[1]), mxGetPr(prhs[2]), 1.0e-6);

    plhs[0] = mxCreateDoubleMatrix(1, dims[1], mxREAL);
    double * xout = mxGetPr(plhs[0]);
    
    for (int i=0; i<dims[1]; i++){
        xout[i] = result.at(i);
    }

}




