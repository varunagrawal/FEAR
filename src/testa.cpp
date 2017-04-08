#include "Library/hog.hpp"
#include <fstream>
#include <dirent.h>
#include <map>
#include <cmath>

#define TEST_SET 100
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
    
    string MAP[] = {"Neutral",
                    "ANGER",
                    "None",
                    "DISGUST",
                    "FEAR",
                    "HAPPY",
                    "SADNESS",
                    "SURPRISE"};
    cout << MAP[7] << endl;
    cout << "sadfasd" << endl;
    //Load classifier  
    CvSVM SVM;
    SVM.load("Library/mixed_SVM_old.xml");
    

    char* dirname = argv[1];
    DIR *pDIR;
    struct dirent *entry;
    
    int num_correct = 0;
    
    if(pDIR = opendir(dirname))
    {
        for(int i=0; i< TEST_SET; i++)
        {
            entry = readdir(pDIR);
            if(!(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..")==0))
            {
                string filePath="";
                string dirn = dirname;
                string file = entry->d_name;
                filePath = dirn + "/" + file;
                
                Mat I = imread(filePath, CV_LOAD_IMAGE_COLOR);
               
                Mat features;
              
                features = featureDetect(I,2,5,26);
                       
                float response = SVM.predict(features);
                cout << response << " ";
                int r = response;
                cout << file << "\tPrediction: " << MAP[r] << endl;

				Mat resized;
                resize(I, resized, Size(), 480.0/I.cols, 480.0/I.rows, INTER_AREA);
				namedWindow("win", CV_WINDOW_AUTOSIZE);
                imshow("win",resized);
                waitKey(0);
            }
        }
        closedir(pDIR);
    }  
    cout << num_correct << " out of " << TEST_SET; 
}
