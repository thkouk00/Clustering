#include "../../include/Hypercube/cmain_func.h"

using namespace std;

void cube_Search_Neighbors(std::map<std::vector<double>, std::vector<double>>& map, HashTable* cube, Cluster** cluster, std::vector<std::vector<double>>& dataset, std::vector<std::vector<double>>& queryset, std::vector<std::string>& id, int& k, int& M, int& probes, int& w, bool& k_means_flag)
{
	std::map<int,bool> mymap;
	// std::map<int,bool>::iterator it;

	bool euclidean_flag = 1;
	double Radius = 0.0;
	// int table_lines = 0;

	// cube_storeDataset(dataset, id,input_file, table_lines,euclidean_flag,Radius);
	if (k == -1)
		k = (int)log2(dataset.size());
	int number_of_vertices = pow(2,k); 	
	cout <<"Table_lines "<<dataset.size()<<std::endl;
	cout <<"Number of vertices "<<number_of_vertices<<std::endl;
	
	//structure to track assigned points
	std::map<std::vector<double>, MapNode> assigned_elements;
	// search neighbors from query_file ***Euclidean Distance***
	cube_search_neighbors(assigned_elements, cube, id, queryset, mymap, M, probes,k, w, number_of_vertices, euclidean_flag);
	
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
					if (queryset[l] == dataset[i])
						continue;
					double temp_dist = Euclidean_Distance(queryset[l], dataset[i]);
					
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
			cout <<"****WAS HERE****"<<std::endl;
			continue;
		}
		else
		{
			//check if point is centroid
			qit = find(queryset.begin(), queryset.end(), dataset[i]);
			if (qit != queryset.end())
				continue;
			double tmp_dist;
			double min_distance;
			int position;
			int second_best;
			double second_dist = 999999;
			//find nearest centroid
			for (int j=0;j<queryset.size();j++)
			{
				tmp_dist = Euclidean_Distance(dataset[i], queryset[j]);
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
					second_dist = tmp_dist;
					second_best = j;
				}

			}

			MapNode node;
			node.set_info(position, second_best, 0, min_distance);
			assigned_elements.insert ( std::pair<std::vector<double>, MapNode>(dataset[i],node) );
			
			int second_best_cluster_temp = 0;
			Info info(dataset[i],id[i],i,second_best_cluster_temp,min_distance);
			cluster[position]->InsertPoint(info);
			if (k_means_flag)
				map[dataset[i]] = queryset[position];
		}
	}
}



// void cube_Search_Neighbors(char* input_file, char* query_file, int& k, int& w, int& M, int& probes)
// {
// 	std::map<int,bool> mymap;
// 	std::map<int,bool>::iterator it;

// 	std::vector<std::string> id;
// 	std::vector<std::vector<double>> dataset;
// 	bool euclidean_flag = 1;
// 	double Radius = 0.0;
// 	int table_lines = 0;

// 	cube_storeDataset(dataset, id,input_file, table_lines,euclidean_flag,Radius);
// 	if (k == -1)
// 		k = (int)log2(table_lines);
// 	int number_of_vertices = pow(2,k); 	
// 	cout <<"Table_lines "<<table_lines<<std::endl;
// 	cout <<"Number of vertices "<<number_of_vertices<<std::endl;
	
// 	// hypercube structure to hold vertices
// 	cube_HashTable *cube = new cube_HashTable(number_of_vertices);
// 	if (euclidean_flag)
// 		cube->cube_hashDataset(dataset, id, mymap, k, w);
// 	else
// 		cube->cube_hashDataset(dataset, id, k);
	
// 	int queryset_lines = 0;
// 	std::vector<std::vector<double>> queryset;
// 	id.clear();
// 	cube_storeDataset(queryset, id,query_file, queryset_lines,euclidean_flag,Radius);

// 	// search neighbors from query_file ***Euclidean Distance***
// 	// search_neighbors(cube, id, queryset, mymap, M, probes,k, w, number_of_vertices, Radius,euclidean_flag, outputfile);
// 	cube_search_neighbors(cube, id, queryset, mymap, M, probes,k, w, number_of_vertices, Radius,euclidean_flag);

// 	//free memory
// 	delete cube;
	
// 	free(input_file);
// 	free(query_file);
// 	// input_file = NULL;
// 	// query_file = NULL;

// }