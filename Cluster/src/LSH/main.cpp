#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include "../../include/LSH/HashTable.h"
#include "../../include/LSH/general_functions.h"
#include "../../include/LSH/main_func.h"

using namespace std;

void Usage()
{
	cerr <<"./lsh -d <input file> –q <query file> –k <int> -L <int> -w <int> -ο <output file>"<<endl;
}

int main(int argc, char const *argv[])
{
	//default values
	int k = 4;
	int L = 5;
	int w = 4;
	char *input_file = NULL;
	char *query_file = NULL;
	char *output_file = NULL;
	// read arguments from command line
	for (int i=0;i<argc;i++)
	{
		if (!strcmp(argv[i],"-h"))
		{
			cout <<argv[0]<<" -d <input file> –q <query file> –k <int> -L <int> -w <int> -ο <output file>"<<endl;
			exit(1);
		}
		else if (!strcmp(argv[i],"-d"))
		{
			if (i+1 < argc)
			{
				int len = strlen(argv[i+1]);
				input_file = (char *) malloc(len+1);
				strcpy(input_file,argv[i+1]);
				input_file[len] = '\0';
				cout << "Input file: " << input_file << endl;
			}
			else
			{
				Usage();
				exit(1);
			}
		}
		else if (!strcmp(argv[i],"-q"))
		{
			if (i+1 < argc)
			{
				int len = strlen(argv[i+1]);
				query_file = (char *) malloc(len+1);
				strcpy(query_file,argv[i+1]);
				query_file[len] = '\0';
				cout << "Query file: " << query_file << endl;
			}
			else
			{
				Usage();
				exit(1);
			}
		}
		else if (!strcmp(argv[i],"-k"))
		{
			if (i+1 < argc)
			{
				k = atoi(argv[i+1]);
				cout << "K: " << k << endl;
			}
			else
			{
				Usage();
				exit(1);
			}
		}
		else if (!strcmp(argv[i],"-L"))
		{
			if (i+1 < argc)
			{
				L = atoi(argv[i+1]);
				cout << "L: " << L << endl;
			}
			else
			{
				Usage();
				exit(1);
			}
		}
		else if (!strcmp(argv[i],"-w"))
		{
			if (i+1 < argc)
			{
				w = atoi(argv[i+1]);
				cout << "W: " << w << endl;
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
				int len = strlen(argv[i+1]);
				output_file = (char *) malloc(len+1);
				strcpy(output_file,argv[i+1]);
				output_file[len] = '\0';
				cout << "Output file: " << output_file << endl;
			}
			else
			{
				Usage();
				exit(1);
			}
		}
	}

	string str;
	if (!input_file)
	{
		cout <<"Give input file: ";
		cin >> str;
		input_file = (char *) malloc(str.length()+1);
		strcpy(input_file,str.c_str());
		cout <<str<<endl;
		cout <<input_file<<endl;
	}

	// ask user for query file and output file
	if (!query_file)
	{
		cout <<"Give query file: ";
		cin >> str;
		query_file = (char *) malloc(str.length()+1);
		strcpy(query_file,str.c_str());
		cout <<str<<endl<<query_file<<endl;
	}
	// if (!output_file)
	// {
	// 	cout <<"Give output file: ";
	// 	cin >> str;
	// 	output_file = (char *) malloc(str.length()+1);
	// 	strcpy(output_file,str.c_str());
	// 	cout <<str<<endl<<output_file<<endl;
	// }

	Search_Neighbors(input_file, query_file, k, L, w);

	// free memory
	// for (int i=0;i<L;i++)
	// 	delete hashTables[i];
	// delete[] hashTables;

	// free(input_file);
	// free(query_file);
	free(output_file);
	// input_file = NULL;
	// query_file = NULL;
	// output_file = NULL;
	// int k = 4;
	// int L = 5;
	// int w = 4;
	// //ask user to rerun program or not 
	
	return 0;
}
