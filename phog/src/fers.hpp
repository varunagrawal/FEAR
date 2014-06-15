#include <fstream>
#include <dirent.h>
#include <map>
#include <iostream>
#include <string>

#include "svm.h"
#include "hog.hpp"

using namespace std;
using namespace cv;

void initialize(char* c, CvSVM& SVM)
{
	SVM.load(c);
}

vector<Rect> faceDetect(Mat img)
{
    cvtColor(img, img, CV_RGB2GRAY);

    CascadeClassifier haarCascade(face_cascade_path);
    vector<Rect> detected;

    haarCascade.detectMultiScale(img, detected, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_DO_ROUGH_SEARCH);

    return detected;
}

vector<Mat> resizeAndSplitFace(Mat img, vector<Rect> detected)
{
    cvtColor(img, img, CV_RGB2GRAY);

    Rect r = detected[0];
    
    Mat faceTop = img(cv::Range(r.y, r.y + r.height/2), cv::Range(r.x, r.x + r.width));
    Mat faceBottom = img(cv::Range(r.y + r.height/2, r.y + r.height), cv::Range(r.x, r.x + r.width));

    vector<Mat> faceParts;
    faceParts.push_back(faceTop);
    faceParts.push_back(faceBottom);
    
    return faceParts;
}

Mat featureDetect(Mat img, int no_divs, int no_levels, int no_bins)
{
    Mat PHOG;
    PHOG = phog(img, no_divs, no_levels, no_bins);
    
    return PHOG;
}

int predict_expression(Mat Img, CvSVM& topSVM, CvSVM& bottomSVM, int no_divs, int no_levels, int no_bins)
{
    vector<Rect> faceRect = faceDetect(Img);
    
    if(faceRect.size() == 0)
	return 0;

    vector<Mat> faceParts = resizeAndSplitFace(Img, faceRect);

    Mat top_features  = featureDetect(faceParts[0], no_divs, no_levels, no_bins);
    int top_prediction = topSVM.predict(top_features);

    Mat bottom_features  = featureDetect(faceParts[0], no_divs, no_levels, no_bins);
    int bottom_prediction = bottomSVM.predict(bottom_features);
    
    return top_prediction;
}

void save_model(svm_model *model, char* file)
{
    svm_save_model(file, model);
}

svm_model* load_model(char* loc)
{
    struct svm_model* SVM = svm_load_model(loc);
    return SVM;
}

void fear_test(Mat img, int no_divs, int no_levels, int no_bins)
{
    cvtColor(img, img, CV_RGB2GRAY);
    
    cout << "Starting test" << endl;
    Mat PHOG;
    PHOG = phog(img, no_divs, no_levels, no_bins);
    
    cout << "PHOG calculated!" << endl;

    /*for(int i=0; i<PHOG.rows; i++)
    {
	for(int j=0; j<PHOG.cols; j++)
	{
	    if(isnan(PHOG.at<double>(i, j)))
		cout << "Found nan at " << i << " " << j << endl;
	    //cout << PHOG.at<double>(i, j) << " ";
	}
	//cout << endl;
	}*/
    cout << "Done" << endl;
    
}
