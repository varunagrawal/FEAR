#include "../../include/gabor.h"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
#include<vector>
#include<cmath>
#include<cstdlib>
#include<sstream>

using namespace cv;

/*
  Commandline arguments: image_name x y width height
*/

int main( int argc, char** argv )
{
	
	Mat input = imread(argv[1]);
	string file = argv[1];
	
	
	//int x = atoi(argv[2]);
	//int y = atoi(argv[3]);
	//int width = atoi(argv[4]);
	//int height = atoi(argv[5]);

	//Rect roi( x, y, width, height);
	Mat image;
	
	
	/* Vector Declarations */

	//Store the gabor filtered images
	vector<Mat> gabors;
	gabors.clear();	
	
	//Store the filter orientation value
	vector<double> phis;
	phis.clear();

	//Store the filter displacement value
	vector<int> k_vals;
	k_vals.clear();
	/*End of Vector Declarations*/
	
	
	image = preprocess( input );
	//Mat src( image, roi );

	Mat src = image;

	for(int i=2; i<8; i+=2)
	{	
		for(int u=0; u<6; u++)
		{
			double k = i; //(double)pow(2, -(i+1));
			double phi = CV_PI*u/6.0;
			double sigma = 2*CV_PI;			
			double psi = 90;
			
			// Return a gabor kernel with appropriate specifications
			Mat kernel = gaborKernel(src, sigma, k, phi, psi);
			
			//Mat output(image.size(), image.type());
			Mat dst;

			// Filter the image with the kernel
			filter2D(src, dst, CV_32F, kernel);
			
			// Store the filtered image, k and phi values
			gabors.push_back( dst );			
			phis.push_back( phi );
			k_vals.push_back( i );

			stringstream ss;
			ss.clear();
			ss << i+4;
			
			string n;
			ss >> n;
			n = file + n;
			ss.clear();
			ss << u;
			string t;
			ss >> t;
			n = n + t + ".jpg";
			
			cout << n << endl;
			
			
			imwrite(n, dst);
			
			//imshow("Gabor Test", dst);
			//cvWaitKey(0);
		}
	}
	
	string window_title = "Gabor Test Image ";

	// Display all images and their corresponding filter values
	for( int i=0; i<gabors.size(); i++ )
	{	
		cout << "K value: " << k_vals[i] <<  "	Phi value: " << phis[i] << endl;


		imshow( window_title, gabors[i] );
		cvWaitKey(0);
	}
	
	
	return 0;
}
