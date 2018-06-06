#include <stdio.h>
#include <mex.h>

void image_threshold(double *img , double *output, int height, int width, double threshold ){
    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y++){
            int ind = x * height + y;
            
            if (img[ind] <threshold)
                output[ind]=0;
            else
                output[ind]=1;
        }
    }
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mxArray *img_m;
    mxArray *output_m;
    double *img;
	double *output;
    double threshold;
    img_m = mxDuplicateArray(prhs[0]);
    threshold = mxGetScalar(prhs[1]);
    const mwSize *image_dims = mxGetDimensions(prhs[0]);
    int height = image_dims[0];
    int width = image_dims[1];
    output_m = plhs[0] = mxCreateNumericArray (2, image_dims, mxDOUBLE_CLASS, mxREAL );
    img = (double*)mxGetData(img_m);
    output = (double*)mxGetData(output_m);
    
	image_threshold(img, output, height, width, threshold);

	return;
}
