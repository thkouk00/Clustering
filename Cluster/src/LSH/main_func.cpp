#include "../../include/LSH/main_func.h"

using namespace std;

extern std::vector<std::vector<double>> Distance_Table;
extern std::vector<int> Cluster_position;
extern bool metric;

//dataset = Points , queryset = Cluster_Table
void Search_Neighbors(std::map<std::vector<double>, std::vector<double>>& map, HashTable** hashTables, Cluster** cluster, std::vector<std::vector<double>>& dataset, std::vector<std::vector<double>>& queryset, std::vector<std::string>& id, int& k, int& L, int& w, bool& k_means_flag)
{	
	bool euclidean_flag = 1;

	// std::cout <<endl<< "Number of lines in input file: " << dataset.size()<<std::endl;;
    
    //number of buckets in each hash Table
    int number_of_buckets;
    // metric = 1 euclidean, metric = 0 cosine
    if (metric == 1)
    	number_of_buckets = dataset.size()/4;
	else
		number_of_buckets = pow(2,k);

	// cout <<"Queryset lines "<<queryset.size()<<std::endl;
	
	//structure to track assigned points
	std::map<std::vector<double>, MapNode> assigned_elements;
	// search neighbors from query_file
	search_neighbors(assigned_elements, hashTables, id, queryset, L, k, w, number_of_buckets, euclidean_flag);


	// cout <<"Points assigned from range "<<assigned_elements.size()<<std::endl;
	std::vector<std::vector<double>>::iterator qit;
	std::map<std::vector<double>, MapNode>::iterator it;
	//assign every point to its cluster
	for (int i=0;i<dataset.size();i++)
	{
		//check if point is already assigned
		it = assigned_elements.find(dataset[i]);
		if (it != assigned_elements.end())
		{
			int c_pos;
			int sec_best;
			double sec_best_dist = 999999;
			double rad;
			double Dist;
			
			it->second.get_all(c_pos,sec_best,rad,Dist);
			if (sec_best == -1)
			{
				for (int l=0;l<queryset.size();l++)
				{
					double temp_dist;
					if (k_means_flag)
						temp_dist = Find_Distance(queryset[l], dataset[i],Cluster_position[l],i);
					else
					{
						if (metric == 1)
							temp_dist = Euclidean_Distance(queryset[l], dataset[i]);
						else
							temp_dist = 1 - Cosine_Similarity(queryset[l], dataset[i]);
					}	
					
					if (sec_best_dist > temp_dist && temp_dist > Dist)
					{
						sec_best_dist = temp_dist;
						sec_best = l;
					}
				}
			}

			Info info(dataset[i],id[i],i,sec_best,Dist);
			cluster[c_pos]->InsertPoint(info);
			if (k_means_flag)
				map[dataset[i]] = queryset[c_pos];
		}
		else
		{
			double tmp_dist;
			double min_distance;
			int position;
			int second_best;
			double second_dist = 999999;
			//find nearest centroid
			for (int j=0;j<queryset.size();j++)
			{
				if (metric == 1)
					tmp_dist = Euclidean_Distance(dataset[i], queryset[j]);
				else
					tmp_dist = 1 - Cosine_Similarity(dataset[i], queryset[j]);
				
				if (j == 0)
				{
					position = j;
					min_distance = tmp_dist;
				}
				else if (min_distance > tmp_dist)
				{
					second_best = position;
					second_dist = min_distance;

					position = j;
					min_distance = tmp_dist;
				}
				else if (second_dist > tmp_dist)
				{
					second_best = j;
					second_dist = tmp_dist;
				}

			}
			MapNode node;
			node.set_info(position, second_best, 0, min_distance);
			assigned_elements.insert ( std::pair<std::vector<double>, MapNode>(dataset[i],node) );
			
			Info info(dataset[i],id[i],i,second_best,min_distance);
			cluster[position]->InsertPoint(info);
			if (k_means_flag)
				map[dataset[i]] = queryset[position];
		}
	}
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
