#include "mex.h"

void median_filter(int width, int height, const unsigned char *input, unsigned char *output, int size){
    int rad = floor(size/2);
    
    int filt_size = size*size;
    unsigned char sort[100] = {0};
    int mid = floor(filt_size/2);
    
    // Set 2D arrays for input and output
    unsigned char input2D[1000][1000] = {0};
    unsigned char output2D[1000][1000] = {0};
    
    // Convert 1D array to 2D
    for(int y = 0 ; y < height; y++){
        for(int x = 0; x < width; x++){
            int ind = x*height + y;
            input2D[y][x] = input[ind];
        }
    }
    for(int i = rad; i < height - rad; i++){
        for(int j = rad; j < width - rad; j++){
            
        // Set temporary variables
        int temp = 0;
        int median = 0;
            
        // Store value of 2D filter into sorted filter array
        for(int k = i - rad; k <= size +i - rad; k++){
            for(int l = j - rad; l <= size +j - rad; l++){
                int pixel = input2D[k][l];
                sort[temp] = pixel;
                temp++;
            }
        }
            // Sort Values
            int temp_sort = 0;
            for(int m = 0; m < filt_size - 1; m++){
                for(int n = m + 1; n < filt_size; n++){
                    if(sort[m] > sort[n]){
                        temp_sort = sort[m];
                        sort[m] = sort[n];
                        sort[n] = temp_sort;
                    }
                }
            }
            // Sorted arrays middle value
            median = sort[mid];
            
            // Locate median
            int midrow = floor((i - rad + size +i - rad)/2);
            int midcol = floor((j - rad + size +j - rad)/2);
            
            // Store located median into the 2D output array
            output2D[midrow][midcol] = median;
        }
    }
    
    // Convert 2D array back to 1D output array
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            int ind = x*height + y;
            output[ind] = output2D[y][x];
        }
    }
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    
    const mxArray *img = prhs[0];
    mwSize ndims = mxGetNumberOfDimensions(img);
    const mwSize *dims = mxGetDimensions(img);
    int height   = dims[0];
    int width    = dims[1];
    int size = mxGetScalar(prhs[1]);
    mxClassID input_type = mxGetClassID(img);
    mxArray *output = mxCreateNumericArray(ndims, dims, input_type, mxREAL);
    plhs[0] = output;
    
    if (mxIsUint8(img)){
        const unsigned char *img_ptr = (unsigned char *)mxGetData(img);
        unsigned char *out_ptr = (unsigned char *)mxGetData(output);
        
        median_filter(width, height, img_ptr, out_ptr, size);
    }
}