%% 3.1.1 XDoG
img = imread('digital_orca_blurred.png');
%if the image needs to converted to greyscale apply the line below
%img = rgb2gray(img);
img = im2double (img);
out = XDoG(img,0.6,1.5,100);
figure(1);
imshow(img); title('original image');
figure(2);
imshow(out); title('output');
%% 3.1.1 Hard Threshold
mex hard_threshold.c
img = imread('digital_orca_blurred.png');
%if the image needs to converted to greyscale apply the line below
%img = rgb2gray(img);
img = im2double (img);
out = XDoG(img,0.6,1.5,50);
out = hard_threshold(out,0.5);
figure(1);
imshow(img); title('original image');
figure(2);
imshow(out); title('output');

%% 3.1.1 Soft Threshold
mex soft_threshold.c
img = imread('digital_orca_blurred.png');
%if the image needs to converted to greyscale apply the line below
%img = rgb2gray(img);
img = im2double (img);
out = XDoG(img,0.6,1.5,50);
out = soft_threshold(out,0.5,6);
figure(1);
imshow(img); title('original image');
figure(2);
imshow(out); title('output');
%% 3.1.1 Three-tone
mex three_tone.c
img = imread('digital_orca_blurred.png');
%if the image needs to converted to greyscale apply the line below
%img = rgb2gray(img);
img = im2double (img);
out = XDoG(img,0.6,1.5,50);
out = three_tone(out);
figure(1);
imshow(img); title('original image');
figure(2);
imshow(out); title('output');
% 3.2.1
mex median_filter.c
img = imread('polar.png');
%if the image needs to converted to greyscale apply the line below
%img = rgb2gray(img);
img1 = median_filter(img,3);
figure(1);
imshow(img); title('original image');
figure(2);
imshow(img1); title('output');

%% 3.2.2
mex spatial_filter.c
mex image_threshold.c
mex invert_grey.c
img=imread('polar.png');
%if the image needs to converted to greyscale apply the line below
%img = rgb2gray(img);
img = im2double(img);
H = [-1 0 1; -1 0 1; -1 0 1];
Gradx = spatial_filter(img, H);
Grady = spatial_filter(img, H);
GradMag = sqrt(Grady.^2 + Gradx.^2);
out = image_threshold(GradMag, 0.2);
img2 = invert_grey(out);
figure(1);
imshow(img); title('original image');
figure(2);
imshow(img2); title('output');

%% 3.2.3 (Run Section 3.2.1. and 3.2.2 first, in order to run 3.2.3)
mex combine.c
img1 = im2double(img1);
img2 = padarray(img2,[1 1]);
img3 = combine(img1,img2);
figure(1);
imshow(img3);title('output');

%% 3.2.4 [Bonus]
img4 = XDoG(img3,0.6,1.5,100);
figure(1);
imshow(img4); title('output');
