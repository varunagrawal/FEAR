#include <fstream>
#include <dirent.h>
#include <map>
#include <iostream>
#include <string>

#include "fear.hpp"

using namespace std;
using namespace cv;

void train(int TRAIN_SET, ifstream& in, string path, Mat& trainingData, Mat& labels)
{   
    for(int i=0; i < TRAIN_SET; i++)
    {
	int label;
        string filename;

        in >> filename;
	
	if(filename != "")    
            in >> label;
	        
	filename = path + filename + ".png";
	cout << "Loading image: " + filename << endl;

	Mat img = imread(filename, CV_LOAD_IMAGE_COLOR);
 	
	Mat features = featureDetect(img, 2, 5, 26);
	cout << "Detecting..." << endl;
	
	int expression = label;
	trainingData.push_back(features);
	labels.push_back(expression);
    }
}	

void test()
{
    Mat img = imread("../dataset/Images/S005_001_00000011.png", CV_LOAD_IMAGE_COLOR);
    imshow("test image", img);
    waitKey(0);

    fear_test(img, 2, 5, 26);

}

int main(int argc, char **argv)
{
    //DIR *pDIR;
    //struct dirent *entry;
    map<string,int> expmap;
    map<string, int>::iterator it;
    
    int TRAIN_SET = 649;

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

    /*****
	  Train on MUG Dataset
    *****/
    //ifstream in("training_set.txt"); 
    //train(TRAIN_SET1, in, "MUG/", trainingData, labels);

    /*****
	  Train on Cohn-Kanade Dataset
    *****/
    /*ifstream in("../dataset/cohn_data_final.txt");

    //train(TRAIN_SET, in, "../dataset/Images/", trainingData, labels);

    cout << "Training of Cohn done." << endl;
    

    // Set up SVM
    CvSVMParams params;
    params.svm_type = CvSVM::C_SVC;
    params.kernel_type = CvSVM::LINEAR;
    
    CvSVM SVM;
    SVM.train(trainingData, labels, Mat(), Mat(), params);
    
    CvStatModel *model = new CvSVM(SVM);
    model->save("trained_SVM.xml");
    cout << "Training of SVM complete" << endl;
    */

    test();

    return 0;
} 
