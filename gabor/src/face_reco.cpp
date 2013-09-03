#include "cv.h"  
#include "highgui.h"  
  
#include <stdio.h>  
#include <stdlib.h>  
  
  
static CvMemStorage* storage_face = 0; //Memory Storage to Sore faces  
  
static CvHaarClassifierCascade* cascade_face = 0;   
  
void detect_and_draw( IplImage* image );  
  
//Haar cascade - if your openc CV is installed at location C:/OpenCV2.0/  
const char* cascade_name_face ="/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml";
  

int main( int argc, char** argv )  
{  
 	IplImage  *image =0;  
 	image = cvLoadImage(argv[1],1);  
 	if(!image)  
 	{  
         	printf("Error loading image\n");  
         	return -1;  
    	}  
     
    	cascade_face = (CvHaarClassifierCascade*)cvLoad( cascade_name_face, 0, 0, 0 );  
      
    	if( !cascade_face )  
    	{  
        	printf("ERROR: Could not load classifier of face  cascade\n" );  
        	return -1;  
    	}  
  
    	storage_face = cvCreateMemStorage(0);  
    	cvNamedWindow( "result", 1 );  
      
    	// Call function to detect and Draw rectagle around face  
    	detect_and_draw( image);  
  
    	// Wait for key event.   
    	cvWaitKey(0);  
                 
    	// release resourses  
    	cvReleaseImage( &image );  
 	cvReleaseHaarClassifierCascade(&cascade_face );  
 	cvReleaseMemStorage( &storage_face);  
    	cvDestroyWindow("result");  
  
    	return 0;  
}  
  
////////////////////////////  Function To detect face //////////////////////////  
  
void detect_and_draw( IplImage* img )  
{  
  
    	double scale = 2;  
      
    	// create a gray image for the input image  
    	IplImage* gray = cvCreateImage( cvSize(img->width,img->height), 8, 1 );  
    	// Scale down the ie. make it small. This will increase the detection speed  
    	IplImage* small_img = cvCreateImage( cvSize( cvRound (img->width/scale),cvRound (img->height/scale)),8, 1 );  
      
    	int i;  
  
    	cvCvtColor( img, gray, CV_BGR2GRAY );  
	cvResize( gray, small_img, CV_INTER_LINEAR );  
      
 	// Equalise contrast by eqalizing histogram of image  
    	cvEqualizeHist( small_img, small_img );  
      
 	cvClearMemStorage( storage_face);  
  
    	if( cascade_face )  
    	{  
         	// Detect object defined in Haar cascade. IN our case it is face  
         	CvSeq* faces = cvHaarDetectObjects( small_img, cascade_face, storage_face, 1.1, 2, 0/*CV_HAAR_DO_CANNY_PRUNING*/, cvSize(30, 30) );  
          
        	// Draw a rectagle around all detected face   
        	for( i = 0; i < (faces ? faces->total : 0); i++ )  
        	{  
            		CvRect r = *(CvRect*)cvGetSeqElem( faces, i );  
   			cvRectangle( img, cvPoint(r.x*scale,r.y*scale),cvPoint((r.x+r.width)*scale,(r.y+r.height)*scale),CV_RGB(255,0,0),3,8,0 );  
    
  		}  
    	}  
  
    	cvShowImage( "result", img );  
    	cvReleaseImage( &gray );  
    	cvReleaseImage( &small_img );  
}  


