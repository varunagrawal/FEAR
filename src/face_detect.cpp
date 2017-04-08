// Include header files
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.h"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include <string>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>

// Create a string that contains the cascade name
const string eye_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
const string face_cascade_name = "haarcascade_frontalface_alt.xml";

// Create Haar classifiers
CascadeClassifier face_cascade = 0;
CascadeClassifier eye_cascade = 0;

std::vector<cv::Rect> detect_face(cv::Mat img)
{
    // Load the cascades
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); return NULL; };

    std::vector<cv::Rect> faces;
    Mat img_gray;

    cv::cvtColor(img, img_gray, COLOR_BGR2GRAY);
    cv::equalizeHist(img_gray, img_gray);

    face_cascade.detectMultiScale(img_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, cv::Size(30, 30));

    return faces;
}


std::vector<cv::Rect> detect_eyes_in_face(cv::Mat faceROI)
{
    if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading eyes cascade\n"); return NULL; };

    std::vector<cv::Rect> eyes;
    eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0|CASCADE_SCALE_IMAGE, cv::Size(30, 30));

    return eyes;
}
