#include "../include/main_func.h"

using namespace std;

void Search_Neighbors(Cluster** cluster, std::vector<std::vector<double>>& dataset, std::vector<std::vector<double>>& queryset, std::vector<std::string>& id, double& Radius, int& k, int& L, int& w)
{
	//construct lsh
	// int hashTable_lines = 0;
	
	bool euclidean_flag = 1;

	std::cout <<endl<< "Number of lines in input file: " << dataset.size()<<std::endl;;
    
    //number of buckets in each hash Table
    int number_of_buckets;
    if (euclidean_flag)
    {
    	number_of_buckets = dataset.size()/4;
		// number_of_buckets = hashTable_lines/4;
    }
	else
		number_of_buckets = pow(2,k);

	 //create L hash_tables
	HashTable **hashTables;	
	hashTables = new HashTable*[L];
	for (int i=0;i<L;i++)
	{
		hashTables[i] = new HashTable(number_of_buckets);
		if (euclidean_flag)
			hashTables[i]->hashDataset(dataset,id,k,w);
		else
			hashTables[i]->hashDataset(dataset,id,k);
	}

	int queryset_lines = 0;
	
	cout <<"Queryset lines "<<queryset.size()<<std::endl;
	
	// search neighbors from query_file
	search_neighbors(hashTables, id, queryset, L, k, w, number_of_buckets, Radius,euclidean_flag);
	for (int i=0;i<L;i++)
		delete hashTables[i];
	delete[] hashTables;
}

//function overload
void Search_Neighbors(char* input_file, char* query_file, int& k, int& L, int& w)
{
	//construct lsh
	int hashTable_lines = 0;
	std::vector<std::string> id;
	std::vector<std::vector<double>> dataset;
	bool euclidean_flag = 1;
	double Radius=0;
	//store dataset in memory for faster and multiple times access 
	storeDataset(dataset, id,input_file, hashTable_lines,euclidean_flag,Radius);
	std::cout <<endl<< "Number of lines in input file: " << hashTable_lines<<std::endl;;
    
    //number of buckets in each hash Table
    int number_of_buckets;
    if (euclidean_flag)
		number_of_buckets = hashTable_lines/4;
	else
		number_of_buckets = pow(2,k);

	 //create L hash_tables
	HashTable **hashTables;	
	hashTables = new HashTable*[L];
	for (int i=0;i<L;i++)
	{
		hashTables[i] = new HashTable(number_of_buckets);
		if (euclidean_flag)
			hashTables[i]->hashDataset(dataset,id,k,w);
		else
			hashTables[i]->hashDataset(dataset,id,k);
	}

	int queryset_lines = 0;
	std::vector<std::vector<double>> queryset;
	
	id.clear();
	
	//store queryset in memory for faster and multiple times access 
	storeDataset(queryset, id,query_file, queryset_lines,euclidean_flag,Radius);
	cout <<"Queryset lines "<<queryset_lines<<std::endl;
	
	// search neighbors from query_file
	// search_neighbors(hashTables, id, queryset, L, k, w, number_of_buckets, Radius,euclidean_flag, outputfile);
	search_neighbors(hashTables, id, queryset, L, k, w, number_of_buckets, Radius,euclidean_flag);
	for (int i=0;i<L;i++)
		delete hashTables[i];
	delete[] hashTables;

	free(input_file);
	free(query_file);
	// free(output_file);
	input_file = NULL;
	query_file = NULL;
}
