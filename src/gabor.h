/*
  Author: Varun Agrawal
  
  Header file for Gabor Kernel and Gabor Jet matching techniques.

*/

#include<cv.h>
#include<cmath>

#ifndef	GABOR_H
#define GABOR_H

using namespace std;
using namespace cv;

// Preprocess the Input image for filtering
Mat preprocess( Mat in );


// Returns a gabor kernel according to specifications
Mat gaborKernel( Mat src, double sigma, double kv, double phi, double psi );


// Similarity function for the points
Mat similarity( vector<Mat> J, vector<double> phi, vector<double> K, vector<double> phi_dash );

#endif

