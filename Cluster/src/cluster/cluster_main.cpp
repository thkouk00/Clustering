#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include "../../include/cluster/cluster_main_func.h"

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
	std::string metric = "euclidean";
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
	
	// check if arguments are correct
	if (input_file.size() == 0 || output_file.size() == 0)
	{
		cout <<"Please give correct input and output file"<<std::endl;
		exit(-1);
	}
	
	int k = 3;		//cluster number
	int k_lsh = 4;
	int k_cube = -1;	// if -1 then compute k_cube with default way
	int L = 5;
	int w = 200; 	//project1 default was 4
	int M = 10;
	int probes = 2;
	string line;
	string tok;
	ifstream myfile (conf_file);
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			std::istringstream iss (line);
			while(!iss.eof())
			{
				// string tok;
				iss >> tok;
				if (tok == "number_of_clusters:")
				{
					iss >> tok;
					k = stoi(tok);
				}
				else if (tok == "number_of_hash_functions_lsh:")
				{
					iss >> tok;
					k_lsh = stoi(tok);
				}
				else if (tok == "number_of_hash_functions_cube:")
				{
					iss >> tok;
					k_cube = stoi(tok);
				}
				else if (tok == "number_of_hash_tables:")
				{
					iss >> tok;
					L = stoi(tok);
				}
				else if (tok == "w:")
				{
					iss >> tok;
					w = stoi(tok);
				}
				else if (tok == "probes:")
				{
					iss >> tok;
					probes = stoi(tok);
				}
				else if (tok == "M:")
				{
					iss >> tok;
					M = stoi(tok);
				}
			}
			cout << line << '\n';
		}
		myfile.close();
	}
	//store every points id
	std::vector<std::string> id;
	std::vector<std::vector<double>> Points;
	std::vector<double> tempv;

	string str;                      // This will store your tokens
	std::ifstream file(input_file);
	int counter = 0;
	while (getline(file, line))
	{
		// cout <<line<<std::endl;
		std::istringstream ss(line);
		std::string token;
		// int id ;
		getline(ss,token,',');
		id.push_back(token);
		counter = 0;
		while (getline(ss, token, ','))   // You can have a different delimiter
		{
			tempv.push_back(stod(token));
			
			// cout <<tempv[counter]<<std::endl;
			counter++;	
		}
		Points.push_back(tempv);
		tempv.clear();
	}
	
	bool metric_flag;
	if (metric == "euclidean")
		metric_flag = 1;
	else if (metric == "cosine")
		metric_flag = 0;
	cluster_main_func(Points, id, output_file, k, k_lsh, k_cube, L, w, M, probes, metric_flag);
	
	return 0;
}