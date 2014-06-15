#include<fstream>
#include<iostream>
#include<string>
#include<getopt.h>

#include "fear.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{      
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
    }

    return 0;
}
