
#include <stdio.h>
#include <mex.h>

void combine(double *img1,double *img2, double *output, int img_h, int img_w){
    for (int y = 0; y < img_h; y++){
        for (int x = 0; x < img_w; x++){
            int ind = x*img_h + y;
            if (img2[ind]<0.2)
                output[ind] = img2[ind];
            else
                output[ind] = img1[ind];
        }
    }
}



void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mxArray *img1_m;
    mxArray *img2_m;
    mxArray *output_m;
    double *img1;
    double *img2;
    double *output;
    img1_m = mxDuplicateArray(prhs[0]);
    img2_m = mxDuplicateArray(prhs[1]);
    const mwSize *image_dims = mxGetDimensions(prhs[1]);
    int img_h = image_dims[0];
    int img_w = image_dims[1];
    output_m = plhs[0] = mxCreateNumericArray (2, image_dims, mxDOUBLE_CLASS, mxREAL );
    img1 = (double*)mxGetData(img1_m);
    img2 = (double*)mxGetData(img2_m);
    output = (double*)mxGetData(output_m);
    
    combine(img1, img2, output, img_h, img_w);
    
    return;
}
