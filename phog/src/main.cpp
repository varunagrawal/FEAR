#include<fstream>
#include<iostream>
#include<string>
#include<getopt.h>

#include "fear.hpp"

using namespace std;
using namespace cv;

string get_file(string type, int div, int levels, int bins)
{
    char* x = new char[41];

    sprintf(x, "phog_classifier_%s_div%d_lvl%d_bins%d.xml", type.c_str(), div, levels, bins);

    string str = x;

    return str;
}

CvSVMParams get_params()
{
    CvSVMParams params;
    params.svm_type = CvSVM::C_SVC;
    params.kernel_type = CvSVM::LINEAR;

    return params;
}


void train_SVM(Mat trainingData, Mat labels, string filename)
{
    cout << "Training SVM " << filename << endl;
    CvSVM SVM;
    SVM.train(trainingData, labels, Mat(), Mat(), get_params());

    //CvStatModel *model = new CvSVM(SVM);
    SVM.save(filename.c_str());
    
    cout << "SVM training complete" << endl;
}

/****
     Train on Cohn-Kanade Dataset
 ***/
void train()
{
    int divs = 2, levels = 5, bins = 26;

    ifstream in("../dataset/cohn_data_final.txt");
    string path = "../dataset/Images/train/";

    const int TRAIN_SET = 649;

    Mat trainingDataTop;
    Mat trainingDataBottom;
    Mat labels;

    for(int i=0; i<TRAIN_SET; i++)
    {
	int label;
	string filename;
	
	in >> filename;

	if(filename != "")
	{
	    in >> label;
	}

	filename = path + filename + ".png";

	Mat img = imread(filename, CV_LOAD_IMAGE_COLOR);

	vector<Mat> features = get_phog_features(img, divs, levels, bins);

	trainingDataTop.push_back(features[0]);
	trainingDataBottom.push_back(features[1]);

	labels.push_back(label);
    }

    train_SVM(trainingDataTop, labels, get_file("top", divs, levels, bins));
    train_SVM(trainingDataBottom, labels, get_file("bottom", divs, levels, bins));
}

int main(int argc, char** argv)
{      
    //train();
    /*
    while(1)
    {
	static struct option long_options[] = 
	    {
		{"option", required_argument, 0, 'o'},
		{"path", required_argument, 0, 'p'}
	    };
	
	int c;
	int option_index = 0;
	
	c = getopt_long(argc, argv, "o:p:", long_options, &option_index);
	
	if(c == -1)
	    break;

	switch(c)
	{
	case 'o':
	    printf("option -o with value %s\n", optarg);
	    break;
	    
	case 'p':
	    printf("option -p with value %s\n", optarg);
	    break;
	    
	case '?':
	    if(optopt == 'o' || optopt == 'p')
	    {
		fprintf(stderr, "Option requires an argument\n");
	    }
	    else if(isprint(optopt))
	    {
		fprintf(stderr, "Unknown option %c\n", optopt);
	    }
	    else
	    {
		fprintf(stderr, "Unknown option character\n");
	    }
	    break;
	    
	}
	}*/

    return 0;
}
