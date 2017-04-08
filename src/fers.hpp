#include <fstream>
#include <dirent.h>
#include <map>
#include <iostream>
#include <string>
	
#include "hog.hpp"

using namespace std;
using namespace cv;

int initialize(char* c, CvSVM& SVM)
{
	SVM.load(c);
}

int predict_expression(Mat Img, CvSVM& SVM, int no_divs, int no_levels, int no_bins)
{
	Mat features  = featureDetect(Img, no_divs, no_levels, no_bins);
	
	int prediction = SVM.predict(features);

	return prediction;
}
