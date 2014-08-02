void fear_test(Mat img, int no_divs, int no_levels, int no_bins)
{
    cvtColor(img, img, CV_RGB2GRAY);
    
    cout << "Starting test" << endl;
    Mat PHOG;
    PHOG = phog(img, no_divs, no_levels, no_bins);
    
    cout << "PHOG calculated!" << endl;

    /*for(int i=0; i<PHOG.rows; i++)
    {
	for(int j=0; j<PHOG.cols; j++)
	{
	    if(isnan(PHOG.at<double>(i, j)))
		cout << "Found nan at " << i << " " << j << endl;
	    //cout << PHOG.at<double>(i, j) << " ";
	}
	//cout << endl;
	}*/
    cout << "Done" << endl;
    
}
