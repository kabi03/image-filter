#include <stdio.h>
#include <mex.h>
void ThreeTone(double *img , double *output, int img_h, int img_w){
 for (int y = 0; y < img_h; y++)
        for (int x = 0; x < img_w; x++){
            int ind = x*img_h + y;
            output[ind] = 1 - img[ind];
        }
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mxArray *img_m;
    mxArray *output_m;
    double *img;
    double *output;
    img_m = mxDuplicateArray(prhs[0]);
    const mwSize *image_dims = mxGetDimensions(prhs[0]);
    int img_h = image_dims[0];
    int img_w = image_dims[1];
    output_m = plhs[0] = mxCreateNumericArray (2, image_dims, mxDOUBLE_CLASS, mxREAL);
    img = (double*)mxGetData(img_m);
    output = (double*)mxGetData(output_m);
    ThreeTone(img, output, img_h, img_w);
    
    return;
}