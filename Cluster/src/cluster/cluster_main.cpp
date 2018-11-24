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
#include "../../include/cluster/Silhouette.h"
#include "../../include/LSH/HashTable.h"

using namespace std;

void Usage()
{
	cerr <<"./cluster -i <input file> –c <configuration file> –o <output file> -d <metric>"<<endl;
}

int main(int argc, char const *argv[])
{
	//temp k kanonika to pairnw apo to config
	int k = 3;
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
		else if (!strcmp(argv[i],"-k"))
		{
			if (i+1 < argc)
			{
				k = stoi(argv[i+1]);
				cout << "K : " << k << endl;
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
	// int k = 50;
	
	// initialization algorithms
	Random_Initialization(Cluster_Table, Points, k);
	// K_means_plusplus(Cluster_Table, Points, k);
	Cluster** cluster = new Cluster*[Cluster_Table.size()];
	for (int i=0;i<Cluster_Table.size();i++)
		cluster[i] = new Cluster;

	int k_lsh = 4;
	int L = 5;
	int w = 300;

	//ean exw lsh ftiaxe th domi hastables mia fora 
	//na dokimasw /4 kai /8 kai na peiraxw kai to w se mikra px 2
	// int number_of_buckets = Points.size()/4;
	// HashTable **hashTables = new HashTable*[L];
	// for (int i=0;i<L;i++)
	// {
	// 	hashTables[i] = new HashTable(number_of_buckets);
	// 	hashTables[i]->hashDataset(Points,id,k_lsh,w);
	// }
	std::map<std::vector<double>, std::vector<double>> new_map;
	std::map<std::vector<double>, std::vector<double>> old_map;

	bool k_means_flag = 1;
	bool flag = 1;
	int max_iter = 0;
	while (flag)
	{		
		// cout <<"LOOP "<<loop<<std::endl;
		Lloyds_Assignment(new_map, cluster, Points, Cluster_Table, id,k_means_flag);
		if (max_iter == 10)
			break;
		
		// LSH_Assignment(new_map, hashTables, cluster, Points, Cluster_Table, id, k_lsh, L, w, k_means_flag);
		
		if (k_means_flag)
		{
			//no change in assignments
			if (new_map == old_map)
			{
				cout <<"NEWMAP size "<<new_map.size()<<std::endl;
				cout <<"OLDMAP size "<<old_map.size()<<std::endl;
				break;
			}
			else
			{
				cout <<"NEWMAP size "<<new_map.size()<<std::endl;
				cout <<"OLDMAP size "<<old_map.size()<<std::endl;
				std::vector<std::vector<double>>::iterator pointIt;
				for (int n=0;n<Points.size();n++)
				{
					pointIt = find(Cluster_Table.begin(),Cluster_Table.end(),Points[n]);
					if (pointIt != Cluster_Table.end())
						continue;
				}
				// old_map.clear();
				old_map = new_map;
				// new_map.clear();
			}
		}


		PAM_improved(cluster, Points, Cluster_Table, id,flag);
		// cout <<"After Pam flag is "<<flag<<std::endl;
		// k_means(cluster, Points, Cluster_Table, id);
		max_iter++;
		if (k_means_flag)
			new_map.clear();
	}

	cout <<"CLUSTER TABLE "<<Cluster_Table.size()<<std::endl;
	for (int i=0;i<Cluster_Table.size();i++)
	{
		// std::vector<std::vector<double>>::iterator iterat;
		// iterat = find(Points.begin(),Points.end(),Cluster_Table[i]);
		// if (iterat != Points.end())
		// 	cout <<"BRETHIKE MISTI MOY"<<std::endl;
		cout <<"------------------------------------------------------"<<std::endl;
		cout <<"ClusteR "<<i<<" is: "<<std::endl;
		std::vector<double> P = Cluster_Table[i];
		// for (int j=0;j<P.size();j++)
		// 	cout <<P[j]<<',';
		// cout <<std::endl;
		std::vector<Info> v = cluster[i]->get_array();
		cout <<"**ASSIGNED POINTS size **"<<v.size()<<std::endl;	
		// for (int j=0;j<v.size();j++)
		// {
		// 	Info info = v[j];
		// 	std::vector<double> point;
		// 	int id;
		// 	point = info.get_point();
		// 	std::vector<std::vector<double>>::iterator iterat;
		// 	iterat = find(Points.begin(),Points.end(),point);
		// 	if (iterat != Points.end())
		// 		cout <<"BRETHIKE MISTI MOY"<<std::endl;
		// 	id = info.get_Pos_Id();
		// 	for (int l=0;l<point.size();l++)
		// 		cout <<point[l]<<',';
		// 	cout <<" and point id "<<id<<std::endl;
		// }
		cout <<"------------------------------------------------------"<<std::endl;
	}
	cout <<"END CLUSTERING"<<std::endl;	
	cout <<"ITERS "<<max_iter<<std::endl;
	double silhouette = Silhouette(cluster, k);
	cout <<"Silhouette value "<<silhouette<<std::endl;
	// cout <<"Distance between 14,10,21,20,20 and 10,10,11,10,11 is "<<Euclidean_Distance(Points[12], Points[10])<<std::endl;
	// cout <<"Distance between 10,10,11,10,11 and 5,5,6,6,6 is "<<Euclidean_Distance(Points[10], Points[6])<<std::endl;
	return 0;
}