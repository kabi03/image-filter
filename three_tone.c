#include <stdio.h>
#include <mex.h>

void three_tone(double *img , double *output, int img_h, int img_w){
    for (int i = 0; i < img_w; i++)
    {
        for (int j = 0; j < img_h; j++)
        {
            int ind = i * img_h + j;
            
            if (img[ind] <=0.3)
                output[ind]=0;
            else if ((img[ind]>0.3) && (img[ind]<=0.6))
                output[ind]= 0.5;
            else   
            output[ind]= 1;
        }
    }
}


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mxArray *img_m;
    mxArray *output_m;
    double *img;
    double *output;
    img_m = mxDuplicateArray(prhs[0]);
    const mwSize *img_dim = mxGetDimensions(prhs[0]);
    int img_h = img_dim[0];
    int img_w = img_dim[1];
    output_m = plhs[0] = mxCreateNumericArray (2, img_dim, mxDOUBLE_CLASS, mxREAL);
    img = (double*)mxGetData(img_m);
    output = (double*)mxGetData(output_m);
    
    three_tone(img, output, img_h, img_w);
    
    return;
}
