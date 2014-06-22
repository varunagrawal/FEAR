#include <fstream>
#include <dirent.h>
#include <map>
#include <cmath>

#include "fear.hpp"

#define TEST_SET 750

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    map <string, int> expmap;
    expmap["NE"] = 0;
    expmap["AN"] = 1;
    expmap["DI"] = 3;
    expmap["FE"] = 4;
    expmap["HA"] = 5;
    expmap["SA"] = 6;
    expmap["SU"] = 7;

    float pcount[8][8],lcount[8];    

    for(int i=0;i<8;i++)
    {
		for(int j=0;j<8;j++)
		{
			pcount[i][j]=0;
			lcount[i]=0;
		}
    }
    

    string MAP[] = {"NEUTRAL",
                    "ANGER",
                    "None",
                    "DISGUST",
                    "FEAR",
                    "HAPPY",
                    "SADNESS",
                    "SURPRISE"};

    //Load classifier  
    CvSVM SVM;
    
    string svm_file;
    cin >> svm_file;
    SVM.load(svm_file);

    string test_set_file;
    ifstream in(test_set_file, ifstream::in); //"test_set.txt"

    int num_correct = 0;

    for(int i=0; i< TEST_SET; i++)
    {
        string filename; 
        in >> filename; 
        if(filename != "")
        {
            int label; 
            in >> label; 
            filename = "MUG_IMAGES/"+filename;
	    
            Mat img = imread(filename, CV_LOAD_IMAGE_COLOR);
            
            Mat features = featureDetect(img, 2, 5, 26);
	    
            int prediction  = SVM.predict(features);
            if(prediction == label){
		cout <<"Prediction: " << prediction << "\tLabel: " << label << "\t" << filename << endl;
		num_correct++;
	    }
	    
	    lcount[label] += 1;
	    pcount[label][prediction] += 1;
	    
	    string exp = MAP[prediction];
	    switch(prediction)
	    {
	    case 0:
		putText(img,exp,Point(0,30),FONT_HERSHEY_DUPLEX,1,Scalar(255,255,255,0),3);
		break;
	    case 1:
		putText(img,exp,Point(0,30),FONT_HERSHEY_DUPLEX,1,Scalar(0,0,255,0),3);
		break;
	    case 3:
		putText(img,exp,Point(0,30),FONT_HERSHEY_DUPLEX,1,Scalar(0,255,255,0),3);
		break;
	    case 4:
		putText(img,exp,Point(0,30),FONT_HERSHEY_DUPLEX,1,Scalar(0,255,0,0),3);
		break;
	    case 5:
		putText(img,exp,Point(0,30),FONT_HERSHEY_DUPLEX,1,Scalar(147,20,255),3);
		break;
	    case 6:
		putText(img,exp,Point(0,30),FONT_HERSHEY_DUPLEX,1,Scalar(255,0,0,0),3);
		break;
	    case 7:
		putText(img,exp,Point(0,30),FONT_HERSHEY_DUPLEX,1,Scalar(211,0,148,0),3);
		break;
	    default:
		putText(img,"None",Point(0,30),FONT_HERSHEY_DUPLEX,1,Scalar(0,0,255,0),3);
		break;
	    }
            
	    namedWindow("win",CV_WINDOW_AUTOSIZE);
	    imshow("win",img);
	    waitKey(0);
        }
    }
    
    for(int i=0;i<8;i++)
    {
	for(int j=0;j<8;j++)
	{
	    if(lcount[i]!=0)
		pcount[i][j] = (float)((float)pcount[i][j]/(float)lcount[i])*100;
	}
    }
    cout << num_correct << " out of " << TEST_SET << endl; 
    for(int i=0; i<8; i++){
	for(int j=0;j<8;j++){
	    cout << pcount[i][j] << " ";
	}
	cout << endl;
    }
    cout<<endl;
    for(int i=0;i<8;i++)
	cout<<lcount[i]<<endl;
}
