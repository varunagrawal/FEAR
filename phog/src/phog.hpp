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
    int N_PHOG = N_DIVS * N_DIVS * N_BINS;
    int BIN_RANGE = (2 * CV_PI);

    Mat Phog;
    Phog = Mat::zeros(1, N_PHOG, CV_32FC1);

    Mat img = Img;

    Mat Ix, Iy;

    //Find orientation gradients in x and y directions
    Sobel(img, Ix, CV_16S, 1, 0, 3);
    Sobel(img, Iy, CV_16S, 0, 1, 3);

    Mat absIx, absIy;
    convertScaleAbs(Ix, absIx);
    convertScaleAbs(Iy, absIy);

    int cellx = img.cols / N_DIVS;
    int celly = img.rows / N_DIVS;
 
    int img_area = img.rows * img.cols;

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
                    grad = static_cast<float>( std::sqrt( 1.0*(px*px) + (py*py) ) );
                    norm_grad = grad / img_area;
                   
                    //Orientation
                    angle = std::atan2(py,px);
                    
                    //convert to (0 to 2*pi)
                    if( angle < 0 )
                        angle += 2 * CV_PI;

                    nth_bin = floor((angle*N_BINS)/(2*CV_PI));

                    //add magnitude of the edges in the phog matrix
                    Phog.at<float>( 0, (m*N_DIVS +n)*N_BINS + static_cast<int>(nth_bin) ) += norm_grad;

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
                max = Phog.at<float>(0, i*N_BINS+j);
        }

	for(j=0; j<N_BINS; j++)
	{
	    if(max == 0)
	    {
		Phog.at<float>(0, i*N_BINS+j) = max;
	    }
	    else
	    {
		Phog.at<float>(0, i*N_BINS+j) /= max;
	    }
	    
	}
    }

    /*
    cout << Phog.cols << " " << Phog.rows << endl;
    if(Phog.cols > 6655)
	cout << "hog 6655: " << Phog.at<float>(0, 6655) << endl;
    */

    return Phog;
}

Mat phog(Mat& Img, int no_divs, int no_levels, int no_bins )
{
    int level;    
    Mat phog = hog(Img, 1, no_bins);  //level 0 phog

    for(level=1; level < no_levels; level++)
    {
        Mat levelHog = hog(Img, (int)pow(no_divs, level), no_bins);

	hconcat(phog, levelHog, phog);
    }

    return phog;
}
