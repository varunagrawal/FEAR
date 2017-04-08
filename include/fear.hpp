#include <fstream>
#include <dirent.h>
#include <map>
#include <iostream>
#include <string>
	
#include "hog.hpp"

using namespace std;
using namespace cv;

CvSVM initialize_svm(char* c)
{
	CvSVM& SVM;
	SVM.load(c);
	return SVM;
}

int predict_expression(Mat img, char* classifier_weights, int no_divs, int no_levels, int no_bins)
{
	// Get the the PHoG features
	Mat features  = featureDetect(img, no_divs, no_levels, no_bins);

	CvSVM SVM = initialize_svm(classifier_weights);
	int prediction = SVM.predict(features);

	return prediction;
}
