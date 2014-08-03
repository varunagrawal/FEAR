#include <fstream>
#include <dirent.h>
#include <map>
#include <iostream>
#include <string>

#include "svm.h"
#include "phog.hpp"

using namespace std;
using namespace cv;

void initialize(char* c, CvSVM& SVM)
{
	SVM.load(c);
}

vector<Rect> face_detect(Mat img)
{
    cvtColor(img, img, CV_RGB2GRAY);

    CascadeClassifier haarCascade(face_cascade_path);
    vector<Rect> detected;

    haarCascade.detectMultiScale(img, detected, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_DO_ROUGH_SEARCH);

    return detected;
}

vector<Mat> resize_and_split_face(Mat img, vector<Rect> detected)
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

Mat feature_detect(Mat img, int no_divs, int no_levels, int no_bins)
{
    Mat resized;
    resize(img, resized, Size(), 480.0/img.cols, 480.0/img.rows, INTER_AREA);

    Mat PHOG = phog(resized, no_divs, no_levels, no_bins);
    
    return PHOG;
}

vector<Mat> get_phog_features(Mat img, int no_divs, int no_levels, int no_bins)
{
    vector<Mat> features;

    vector<Rect> faceRect = face_detect(img);
    
    if(faceRect.size() == 0)
	return features;

    vector<Mat> faceParts = resize_and_split_face(img, faceRect);

    Mat top_features  = feature_detect(faceParts[0], no_divs, no_levels, no_bins);

    Mat bottom_features  = feature_detect(faceParts[1], no_divs, no_levels, no_bins);

    features.push_back(top_features);
    features.push_back(bottom_features);

    return features;
}

vector<int> predict_expression(Mat Img, CvSVM& topSVM, CvSVM& bottomSVM, int no_divs, int no_levels, int no_bins)
{
    vector<int> predictions;
    
    vector<Rect> faceRect = face_detect(Img);
    
    if(faceRect.size() == 0)
	return predictions;

    vector<Mat> faceParts = resize_and_split_face(Img, faceRect);

    Mat top_features  = feature_detect(faceParts[0], no_divs, no_levels, no_bins);
    int top_prediction = topSVM.predict(top_features);

    Mat bottom_features  = feature_detect(faceParts[1], no_divs, no_levels, no_bins);
    int bottom_prediction = bottomSVM.predict(bottom_features);

    predictions.push_back(top_prediction);
    predictions.push_back(bottom_prediction);

    return predictions;
}

/*
  Function to predict class of input data.
  Arguments:
      svm_model* SVM: Support Vector Machine from libSVM.
      Mat data: OpenCV Mat object that has each row as one data point.

  Return: Array of prediction probabilities for each class for each row of data.
*/
double** fear_predict_probability(svm_model* SVM, Mat& data)
{
    struct svm_node *svmVec;
    svmVec = (struct svm_node *)malloc((data.cols+1) * sizeof(struct svm_node));
    
    const int nr_classes = svm_get_nr_class(SVM);

    // Get Data from OpenCV Mat
    double *dataPtr = data.ptr<double>();
    
    double** prob_estimates = (double**)malloc(data.rows * sizeof(double*));
    //new double[nr_classes];
    
    for(int i=0;i<data.rows;i++)
    {
	prob_estimates[i] = (double*)malloc(nr_classes * sizeof(double));
    }

    int r, c;
    for(r=0; r<data.rows; r++)
    {
	for(c=0; c<data.cols; c++)
	{
	    svmVec[c].index = c+1;    // Index starts from 1; Pre-computed kernel starts from 0
	    svmVec[c].value = dataPtr[ r * data.cols + c ];
	}
	svmVec[c].index = -1;

	svm_predict_probability(SVM, svmVec, prob_estimates[r]);
    }

    return prob_estimates;
}

Mat featureDetect(Mat img, int no_divs, int no_levels, int no_bins)
{
    cvtColor(img, img, CV_RGB2GRAY);
    CascadeClassifier haarCascade(face_cascade_path);
    vector <Rect> detected;

    haarCascade.detectMultiScale(img, detected, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_DO_ROUGH_SEARCH);
    Mat face = img(detected[0]);
    Mat resized;

    resize(face, resized, Size(), 480.0/face.cols, 480.0/face.rows, INTER_AREA);
    Mat PHOG;
    PHOG = phog(resized,no_divs, no_levels, no_bins);
    return PHOG;
}
