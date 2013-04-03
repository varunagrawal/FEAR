/*
  Author: Varun Agrawal
  
  Header file for Gabor Kernel and Gabor Jet matching techniques.

*/

#include<cv.h>
#include<cmath>

using namespace std;
using namespace cv;

// Preprocess the Input image for filtering
Mat preprocess( Mat in )
{
	Mat out;
	
	//Convert image to GrayScale
	cvtColor( in, out, CV_BGR2GRAY );
	
	// Convert Image Type and rescale
	out.convertTo( out, CV_32F, 1.0/255, 0 );
	
	return out;
	
}


// Returns a gabor kernel according to specifications
Mat gaborKernel( Mat src, double sigma, double kv, double phi, double psi )
{
	//Kernel size same as the image
	Mat kernel( src.size(), src.type());
	

	//Calculate halfwidth and halfheight
	int hwidth = (src.cols - 1)/2;
	int hheight = (src.rows - 1)/2;
	
	/*
	//Sigma should be 2*PI
	if( sigma != 2*CV_PI )
	{
		sigma = 2 * CV_PI;
	}

	// Creation of the kernel
	for( int y=-hheight; y<=hheight; y++ )
	{
		for( int x=-hwidth; x<=hwidth; x++ )
		{
			double k_square = ( kv * kv );
			double sigma_square = ( sigma * sigma );
			
			double val = k_square / sigma_square;
			val *= (double)exp( (-k_square * (x*x + y*y)) / (2*sigma_square) );
			val *= (double)( (double)cos( kv * (x*cos(phi) + y*sin(phi)) ) - (double)exp(-sigma_square/2) );

						
			kernel.at<float>(hheight + y, hwidth + x) = val;

		}
	}
	
	*/

	sigma = sigma / 10.0;
	kv = kv / 10.0;
	phi = phi;
	psi = CV_PI * psi / 180.0;
	
	for( int y=-hheight; y<=hheight; y++ )
	{
		for( int x=-hwidth; x<=hwidth; x++ )
		{
			double val = exp( -(x*x + y*y) / (2*sigma*sigma) ) * cos( kv*x*cos(phi) + kv*y*sin(phi) + psi );
			kernel.at<float>(hheight + y, hwidth + x) = val;
		}
		
	}
	
	return kernel;

}


// Similarity function for the points
Mat similarity( vector<Mat> J, vector<double> phi, vector<double> K, vector<double> phi_dash )
{
	double val = 0;
	double a, a_dash;
	double a_square = 0, a_dash_square = 0;
	
	// Store the similarity values in this Matrix
	Mat X( J[0].rows, J[0].cols, CV_32F);
		
	for( int x=0; x < J[0].rows; x++ )
	{
		for( int y=0; y<J[0].cols; y++ )
		{
			a_square = 0;
			a_dash_square = 0;
			
			// Do the similarity mapping for each point.
			// This is the main similarity matching code for each of the coefficients in the Gabor Jet.
			for(int i=0; i<J.size(); i++)
			{
				a = J[i].at<double>(x, y) / phi[i];
				a_dash = K[i] / phi_dash[i];
				
				// Numerator
				val += a * a_dash * cos( phi[i] - phi_dash[i] );
			
				// Calculating squares for the denominator
				a_square += (a * a);
				a_dash_square += ( a_dash * a_dash );
				
			}
			
			X.at<double>(x, y) = val / ( sqrt(a_square * a_dash_square) );
		   
		}	
	}

	return X;

}



