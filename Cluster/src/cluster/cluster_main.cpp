#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include "../../include/cluster/Initialization.h"

using namespace std;

void Usage()
{
	cerr <<"./cluster -i <input file> –c <configuration file> –o <output file> -d <metric>"<<endl;
}

int main(int argc, char const *argv[])
{
	std::string input_file;
	std::string output_file;
	std::string conf_file;
	std::string metric;
	//read args
	for (int i=0;i<argc;i++)
	{
		if (!strcmp(argv[i],"-h"))
		{
			cout <<argv[0]<<" -i <input file> –c <configuration file> –o <output file> -d <metric>"<<endl;
			exit(1);
		}
		else if (!strcmp(argv[i],"-i"))
		{
			if (i+1 < argc)
			{
				int len = strlen(argv[i+1]);
				// input_file = (char *) malloc(len+1);
				// strcpy(input_file,argv[i+1]);
				// input_file[len] = '\0';
				input_file = argv[i+1];
				cout << "Input file: " << input_file << endl;
			}
			else
			{
				Usage();
				exit(1);
			}
		}
		else if (!strcmp(argv[i],"-c"))
		{
			if (i+1 < argc)
			{
				// int len = strlen(argv[i+1]);
				// query_file = (char *) malloc(len+1);
				// strcpy(query_file,argv[i+1]);
				// query_file[len] = '\0';
				conf_file = argv[i+1];
				cout << "Query file: " << conf_file << endl;
			}
			else
			{
				Usage();
				exit(1);
			}
		}
		else if (!strcmp(argv[i],"-d"))
		{
			if (i+1 < argc)
			{
				metric = argv[i+1];	
				cout << "Metric: " << metric << endl;
			}
			else
			{
				Usage();
				exit(1);
			}
		}
		else if (!strcmp(argv[i],"-o"))
		{
			if (i+1 < argc)
			{
				output_file = argv[i+1];
				cout << "Output file: " << output_file << endl;
			}
			else
			{
				Usage();
				exit(1);
			}
		}
	}

	//store every points id
	std::vector<std::string> id;
	std::vector<std::vector<double>> Points;
	std::vector<double> tempv;

	string str;                      // This will store your tokens
	string line;
	std::ifstream file(input_file);
	int counter = 0;
	while (getline(file, line))
	{
		cout <<line<<std::endl;
		std::istringstream ss(line);
		std::string token;
		// int id ;
		getline(ss,token,',');
		id.push_back(token);
		counter = 0;
		while (getline(ss, token, ','))   // You can have a different delimiter
		{
			tempv.push_back(stod(token));
			
			cout <<tempv[counter]<<std::endl;
			counter++;	
		}
		Points.push_back(tempv);
		tempv.clear();
	}
	cout <<"AFTER"<<std::endl;

	std::vector<std::vector<double>> Cluster_Table;
	int k = 3;

	// for (int ll=0;ll<Points.size();ll++)
	// {
	// 	std::vector<double> tempv = Points[ll];
	// 	for (int q=0;q<tempv.size();q++)
	// 		cout <<tempv[q]<<' ';
	// 	cout <<std::endl;
	// }
	
	Random_Initialization(Cluster_Table, Points, k);
	Cluster_Table.clear();
	K_means_plusplus(Cluster_Table, Points, k);
	

	// K_means_plusplus(cluster,k, num_of_lines, Cluster_Table, Points);

	return 0;
}