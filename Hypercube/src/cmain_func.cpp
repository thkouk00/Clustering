#include "../include/cmain_func.h"

using namespace std;


void Search_Neighbors(char* input_file, char* query_file, int& k, int& w, int& M, int& probes)
{
	std::map<int,bool> mymap;
	std::map<int,bool>::iterator it;

	std::vector<std::string> id;
	std::vector<std::vector<double>> dataset;
	bool euclidean_flag = 1;
	double Radius = 0.0;
	int table_lines = 0;

	storeDataset(dataset, id,input_file, table_lines,euclidean_flag,Radius);
	if (k == -1)
		k = (int)log2(table_lines);
	int number_of_vertices = pow(2,k); 	
	cout <<"Table_lines "<<table_lines<<std::endl;
	cout <<"Number of vertices "<<number_of_vertices<<std::endl;
	
	// hypercube structure to hold vertices
	HashTable *cube = new HashTable(number_of_vertices);
	if (euclidean_flag)
		cube->hashDataset(dataset, id, mymap, k, w);
	else
		cube->hashDataset(dataset, id, k);
	
	int queryset_lines = 0;
	std::vector<std::vector<double>> queryset;
	id.clear();
	storeDataset(queryset, id,query_file, queryset_lines,euclidean_flag,Radius);

	// search neighbors from query_file ***Euclidean Distance***
	// search_neighbors(cube, id, queryset, mymap, M, probes,k, w, number_of_vertices, Radius,euclidean_flag, outputfile);
	search_neighbors(cube, id, queryset, mymap, M, probes,k, w, number_of_vertices, Radius,euclidean_flag);

	//free memory
	delete cube;
	
	free(input_file);
	free(query_file);
	// input_file = NULL;
	// query_file = NULL;

}