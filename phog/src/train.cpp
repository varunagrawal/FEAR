#include <fstream>
#include <dirent.h>
#include <map>
#include <iostream>
#include <string>

#include "hog.hpp"

#define TRAIN_SET1 3080
#define TRAIN_SET2 649

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    //DIR *pDIR;
    //struct dirent *entry;
    map<string,int> expmap;
    map<string, int>::iterator it;
    
    int res_ip;
    expmap["NE"] = 0;
    expmap["AN"] = 1;
    expmap["DI"] = 3;
    expmap["FE"] = 4;
    expmap["HA"] = 5;
    expmap["SA"] = 6;
    expmap["SU"] = 7;

    Mat trainingData;
    Mat labels;
    ifstream in("training_set.txt"); 
    
    // Training data for MUG dataset
    /*for(int i=0; i< TRAIN_SET1; i++)
    {
	string filename;
        in >> filename;
    	
	if(filename != "")
        {
            int label;
            in >> label;
            
	    filename = "MUG/" + filename;
	    Mat img = imread(filename, CV_LOAD_IMAGE_COLOR);
            Mat features = featureDetect(img,2,5,26);
	    int expression = label;
	    
            trainingData.push_back(features);
            labels.push_back(expression);
        }
    }
    cout << "Training of MUG done" << endl;
    */

    ifstream in1("cohn_data_final.txt");
 
    for(int i=0; i < TRAIN_SET2; i++)
    {
        string filename;
        in1 >> filename;
        if(filename != "")
        
            int label;
            in1 >> label;
	    
            filename = filename.insert(9,"000000");
            filename[0] = 'S';
            
	    filename = "../dataset/Images/" + filename + ".png";
	    Mat img = imread(filename, CV_LOAD_IMAGE_COLOR);
 	    
            Mat features = featureDetect(img, 2, 5, 26);
            int expression = label;
            trainingData.push_back(features);
            labels.push_back(expression);
        }
    }	
    
    cout << "Training of Cohn also done. :D" << endl;
    
    //SVM
    CvSVMParams params;
    params.svm_type = CvSVM::C_SVC;
    params.kernel_type = CvSVM::LINEAR;
    
    CvSVM SVM;
    SVM.train(trainingData, labels, Mat(), Mat(), params);
    
    CvStatModel *model = new CvSVM(SVM);
    model->save("trained_SVM.xml");
    cout << "Trained :D" << endl;

    return 0;
} 
