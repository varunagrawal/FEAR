#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

string face_cascade_path = "haarcascade_frontalface_default.xml";

//Input: Grayscale image
//Output: HOG features

Mat hog(Mat &Img, int no_divs, int no_bins)
{
    int N_BINS = no_bins;
    int N_DIVS = no_divs;
    int N_PHOG = N_DIVS*N_DIVS*N_BINS;
    int BIN_RANGE = (2*CV_PI);

    Mat Phog;
    Phog = Mat::zeros(1, N_PHOG, CV_32FC1);

    Mat Img1 = Img;

    Mat Ix, Iy;

    //Find orientation gradients in x and y directions
    Sobel(Img1, Ix, CV_16S, 1, 0, 3);
    Sobel(Img1, Iy, CV_16S, 0, 1, 3);

    Mat absIx, absIy;
    convertScaleAbs(Ix, absIx);
    convertScaleAbs(Iy, absIy);

    int cellx = Img1.cols/N_DIVS;
    int celly = Img1.rows/N_DIVS;
    
    int img_area = Img1.rows * Img1.cols;

    for(int m=0; m < N_DIVS; m++)
    {
        for(int n=0; n < N_DIVS; n++)
        {
             for(int i=0; i<cellx; i++)
             {
                for(int j=0; j<celly; j++)
                {
                    
                    float px, py, grad, norm_grad, angle;
                    float nth_bin;

                    px = static_cast<float>(Ix.at<int16_t>((m*cellx)+i, (n*celly)+j ));
                    py = static_cast<float>(Iy.at<int16_t>((m*cellx)+i, (n*celly)+j ));
                    
                    grad = static_cast<float>(std::sqrt(1.0*px*px + py*py));
                    norm_grad = grad/img_area;
                   
                    //Orientation
                    angle = std::atan2(py,px);
                    
                    //convert to (0 to 2*pi)
                    if( angle < 0)
                        angle+= 2*CV_PI;

                    nth_bin = floor((angle*N_BINS)/(2*CV_PI));

                    //add magnitude of the edges in the phog matrix
                    Phog.at<float>(0,(m*N_DIVS +n)*N_BINS + static_cast<int>(nth_bin)) += norm_grad;

                }
             }
        }
    }  


    //Normalization
    
    for(int i=0; i< N_DIVS*N_DIVS; i++)
    { 
        float max=0;
        int j;
        for(j=0; j<N_BINS; j++)
        {
            if(Phog.at<float>(0, i*N_BINS+j) > max)
                max = Phog.at<float>(0,i*N_BINS+j);
        }
        for(j=0; j<N_BINS; j++)
            Phog.at<float>(0, i*N_BINS+j)/=max;
    }

    return Phog;
}

Mat phog(Mat &Img, int no_divs, int no_levels, int no_bins )
{

    int Level;    
    Mat phog = hog(Img, 1, no_bins);  //level 0 phog
    for(Level=1; Level<no_levels; Level++)
    {

        Mat levelHog = hog(Img, (int)pow(no_divs,Level), no_bins);
        hconcat(phog, levelHog, phog);
    }
    return phog;
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

