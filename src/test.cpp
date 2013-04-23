#include<vector>
#include "cv.h"
#include "highgui.h"
#include "gabor.h"
#include "/usr/include/opencv/cxcore.hpp"
#include<cmath>
#include<iostream>
#include<fstream>


using namespace std;
using namespace cv;

vector<double> getPoints()
{
  vector<double> p;
  fstream fin;
  fin.open("pointsVector.txt", ios::in);

  double point;

  for(int i=0;i<17;i++)
  {
	  fin >> point;
	  p.push_back(point);
	  fin >> point;
	  p.push_back(point);
  }

  return p;
  
}

int main( int argc, char** argv )
{
  Mat in = imread(argv[1]);

  Mat out;
  cvtColor( in, out, CV_BGR2GRAY );
  
  out.convertTo( out, CV_32F, 1.0/255, 0 );

  Mat tI = imread(argv[2]);
  Mat testImage;
  cvtColor(tI, testImage, CV_BGR2GRAY);
  testImage.convertTo(testImage, CV_32F, 1.0/255, 0);

  vector<Mat> gaborImages;
  vector<Mat> groundImages;

  vector<double> phis;
  vector<double> points;

  points = getPoints();

  
  for( int k=-4; k<0; k++ )
  {
      for( int u=0; u<8; u++ )
      {
	      double kv = (double)pow(2, -(k+1));
	      double phi = CV_PI*u/8.0;
	      
	      phis.push_back(phi);
	      
	      double sigma = 2*CV_PI;
	      Mat dst;
	      
	      Mat kernel = gaborKernel( out, kv, phi, sigma );
	      filter2D(out, dst, CV_32F, kernel);
	      gaborImages.push_back(dst);
	      
	      kernel = gaborKernel( testImage, kv, phi, sigma );
	      filter2D(testImage, dst, CV_32F, kernel);
	      groundImages.push_back(dst);
	      
      }
      
  }

  vector< vector< double > >  S;
  vector<double> Si;

  for(int i=0; i<points.size(); i+=2)
  {
	  Si.clear();
      for(int j=0;j<groundImages.size();j++)
      {
	      double s = groundImages[j].at<CV_32F>(i, i+1);

	      Si.push_back(s);
      }

      S.push_back(Si);
  }

  Mat X = similarity(gaborImages, phis, S[0], phis);

  double max = -1.0;
  double x, y;

  for(int i=0;i<X.rows;i++)
  {
	  for(int j=0;j<X.cols;j++)
	  {
		  Point p(i, j);
		  double val = X.at<CV_32F>((Point)p); 
		  if( max < val)
		  {
			  max = val;
			  x = i;
			  y = j;
		  }
	  }
  }

  cout << "Finding the first feature point" << endl;
  cout << "X: " << x << "    Y: " << y << endl; 
  
  return 0;
}
