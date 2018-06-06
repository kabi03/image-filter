#include <stdio.h>
#include <mex.h>
#include <math.h>

void soft_threshold(double *img , double *output, int img_h, int img_w, double threshold, double phi){
    for (int i = 0; i < img_w; i++){
        for (int j = 0; j < img_h; j++){
            int ind = i*img_h + j;
            
            if (img[ind] >threshold)
                output[ind]=1;
            else
                output[ind]= 1 + tanh(phi*(output[ind]-threshold));
        }
    }
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mxArray *img_m;
    mxArray *output_m;
    
    double *img;
    double *output;
    double threshold;
    double phi;
    
    img_m = mxDuplicateArray(prhs[0]);
    threshold = mxGetScalar(prhs[1]);
    phi = mxGetScalar(prhs[2]);
    const mwSize *image_dims = mxGetDimensions(prhs[0]);
    int img_h = image_dims[0];
    int img_w = image_dims[1];
    output_m = plhs[0] = mxCreateNumericArray (2, image_dims, mxDOUBLE_CLASS, mxREAL );
    img = (double*)mxGetData(img_m);
    output = (double*)mxGetData(output_m);
    
    soft_threshold(img, output, img_h, img_w, threshold, phi);
    
    return;
}