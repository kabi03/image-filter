#include "mex.h"

void function(int width, int height, int window_width, int window_height, double *img_ptr,  double *window_ptr, double *output){
    int h_mid, w_mid;
    int l_bound, r_bound, t_bound, b_bound;
    if (((window_height % 2) == 0)&&(window_height>1))
        h_mid=window_height/2-1;
    else
        h_mid=(window_height-1)/2;
    if ((( window_width % 2)==0)&&(window_width>1))
        w_mid=window_width/2-1;
    else
        w_mid=(window_width-1)/2;
    b_bound=height-window_height+1;
    r_bound=width-window_width+1;
    
    for (int i = 0; i < b_bound; ++i){
        
        for (int j = 0; j < r_bound; ++j){
            
            int ind_out=j*(b_bound);
            int ind = j*height;
            output[ind_out+i]=0;
            for (int y = 0; y < window_width; ++y){
                
                int ind = (j+y)*height;
                int f_ind=y*window_height;
                for (int x = 0; x < window_height; ++x){
                    
                    output[ind_out+i]+=img_ptr[ind+i+x]*window_ptr[f_ind+x];
                }
            }
        }
    }
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    
    const mxArray *img = prhs[0];
    const mxArray *h = prhs[1];
    
    mwSize ndims = mxGetNumberOfDimensions(img);
    const mwSize *dims = mxGetDimensions(img);
    mwSize h_ndims = mxGetNumberOfDimensions(h);
    const mwSize *h_dims = mxGetDimensions(h);
    
    int height   = dims[0];
    int width    = dims[1];
    int window_height = h_dims[0];
    int window_width  = h_dims[1];
    int out_demen[2];
    out_demen[0]= height-window_height+1;
    out_demen[1]= width-window_width+1;
    
    mxClassID input_type = mxGetClassID(img);
    mxArray *output = mxCreateNumericArray(ndims, out_demen, input_type, mxREAL);
    plhs[0] = output;
    
    if (mxIsDouble(img)){
        double *img_ptr = (double *)mxGetData(img);
        double *out_ptr = (double *)mxGetData(output);
        double *window_ptr   = (double *)mxGetData(h);
        function(width, height, window_width , window_height ,  img_ptr, window_ptr, out_ptr);
    }
}
