#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include "../../include/cluster/Cluster.h"
#include "../../include/cluster/Initialization.h"
#include "../../include/cluster/Assignment.h"
#include "../../include/cluster/Update.h"

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
	cout <<"AFTER size "<<Points.size()<<std::endl;

	std::vector<std::vector<double>> Cluster_Table;
	int k = 3;

	// for (int ll=0;ll<Points.size();ll++)
	// {
	// 	std::vector<double> tempv = Points[ll];
	// 	for (int q=0;q<tempv.size();q++)
	// 		cout <<tempv[q]<<' ';
	// 	cout <<std::endl;
	// }
	
	// Random_Initialization(Cluster_Table, Points, k);
	// Cluster_Table.clear();
	K_means_plusplus(Cluster_Table, Points, k);
	Cluster** cluster = new Cluster*[Cluster_Table.size()];
	for (int i=0;i<Cluster_Table.size();i++)
		cluster[i] = new Cluster;

	int k_lsh = 4;
	int L = 5;
	int w = 300;

	Cluster **previous_cluster_setup = cluster; 
	bool flag = 1;
	int max_iter = 0;
	// while (flag && max_iter < 3)
	while (flag)
	{		
		// cout <<"LOOP "<<loop<<std::endl;
		Lloyds_Assignment(cluster, Points, Cluster_Table, id);
		// LSH_Assignment(cluster, Points, Cluster_Table, id, k_lsh, L, w);
		
		// if (loops > 0 && k_meansFlag)
		// {
		// 	for (int i=0;i<Cluster_Table;i++)
		// 	{
		// 		if ()
		// 	}
		// }
		for (int i=0;i<Cluster_Table.size();i++)
		{
			cout <<"********************BEFORE PAM*************************"<<std::endl;
			cout <<"CLUSTER TABLE "<<Cluster_Table.size()<<std::endl;
			std::vector<double> P = Cluster_Table[i];
			std::vector<Info> v = cluster[i]->get_array();
			cout <<"Cluster "<<i<<" is: "<<std::endl;
			for (int j=0;j<P.size();j++)
				cout <<P[j]<<',';
			cout <<std::endl;

			cout <<"**ASSIGNED POINTS**"<<std::endl;	
			for (int j=0;j<v.size();j++)
			{
				Info info = v[j];
				std::vector<double> point;
				int id;
				point = info.get_point();
				id = info.get_Pos_Id();
				for (int l=0;l<point.size();l++)
					cout <<point[l]<<',';
				cout <<" and point id "<<id<<std::endl;
			}
			cout <<"------------------------------------------------------"<<std::endl;
		}
		PAM_improved(cluster, Points, Cluster_Table, id,flag);
		// k_means(cluster, Points, Cluster_Table, id);
		cout <<"********************AFTER PAM*************************"<<std::endl;
		cout <<"CLUSTER TABLE "<<Cluster_Table.size()<<std::endl;
		for (int i=0;i<Cluster_Table.size();i++)
		{
			// std::vector<std::vector<double>>::iterator iterat;
			// iterat = find(Points.begin(),Points.end(),Cluster_Table[i]);
			// if (iterat != Points.end())
			// 	cout <<"BRETHIKE MISTI MOY"<<std::endl;
			cout <<"------------------------------------------------------"<<std::endl;
			cout <<"Cluster "<<i<<" is: "<<std::endl;
			std::vector<double> P = Cluster_Table[i];
			for (int j=0;j<P.size();j++)
				cout <<P[j]<<',';
			cout <<std::endl;
			std::vector<Info> v = cluster[i]->get_array();
			cout <<"**ASSIGNED POINTS**"<<std::endl;	
			for (int j=0;j<v.size();j++)
			{
				Info info = v[j];
				std::vector<double> point;
				int id;
				point = info.get_point();
				std::vector<std::vector<double>>::iterator iterat;
				iterat = find(Points.begin(),Points.end(),point);
				if (iterat != Points.end())
					cout <<"BRETHIKE MISTI MOY"<<std::endl;
				id = info.get_Pos_Id();
				for (int l=0;l<point.size();l++)
					cout <<point[l]<<',';
				cout <<" and point id "<<id<<std::endl;
			}
			cout <<"------------------------------------------------------"<<std::endl;
		}
		max_iter++;
	}
	

	return 0;
}