#include "../../include/Hypercube/cmain_func.h"

using namespace std;

extern std::vector<std::vector<double>> Distance_Table;
extern std::vector<int> Cluster_position;
extern bool metric;

void cube_Search_Neighbors(std::map<std::vector<double>, std::vector<double>>& map, HashTable* cube, Cluster** cluster, std::vector<std::vector<double>>& dataset, std::vector<std::vector<double>>& queryset, std::vector<std::string>& id, std::map<int, bool>& coinmap, int& k, int& M, int& probes, int& w, bool& k_means_flag)
{
	bool euclidean_flag = 1;

	int number_of_vertices = pow(2,k); 	
	
	//structure to track assigned points
	std::map<std::vector<double>, MapNode> assigned_elements;
	
	cube_search_neighbors(assigned_elements, cube, id, queryset, coinmap, M, probes,k, w, number_of_vertices, euclidean_flag);
	
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
						temp_dist = Find_Distance(queryset[l], dataset[i], Cluster_position[l], i);
					else
					{
						if (metric == 1)
							temp_dist = Euclidean_Distance(queryset[l], dataset[i]);
						else
							temp_dist = Cosine_Similarity(queryset[l], dataset[i]);	
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
					tmp_dist = Cosine_Similarity(dataset[i], queryset[j]);
				
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