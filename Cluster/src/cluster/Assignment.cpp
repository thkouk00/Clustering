#include "../../include/cluster/Assignment.h"

using namespace std;

extern std::vector<std::vector<double>> Distance_Table;
extern std::vector<int> Cluster_position;
extern bool metric;

void Lloyds_Assignment(std::map<std::vector<double>, std::vector<double>>& map, Cluster **cluster, std::vector<std::vector<double>>& Points, std::vector<std::vector<double>>& Cluster_Table, std::vector<std::string>& point_id, bool& k_means_flag,double& objective)
{
	for (int i=0;i<Cluster_Table.size();i++)
		cluster[i]->clear_structure();
	
	// just check the amount of assigned points
	int counter = 0;
	std::vector<std::vector<double>>::iterator it;
	for (int i=0;i<Points.size();i++)
	{
		int cluster_pos = -1;
		int second_best = -1;
		double min_dist = 0;
		double second_dist = 999999;
		
		for (int j=0;j<Cluster_Table.size();j++)
		{
			double dist;
			if (!k_means_flag)
				dist = Find_Distance(Points[i], Cluster_Table[j], i, Cluster_position[j]);
			else
			{
				if (metric == 1)
					dist = Euclidean_Distance(Points[i], Cluster_Table[j]);
				else
					dist = 1 - Cosine_Similarity(Points[i], Cluster_Table[j]);
			}
			
			if (j == 0)
			{
				min_dist = dist;
				cluster_pos = j;
			}
			else if (min_dist > dist)
			{
				// update second best cluster
				second_dist = min_dist;
				second_best = cluster_pos;
				// update new cluster position
				min_dist = dist;
				cluster_pos = j;
			}
			else if (second_dist > dist && dist != min_dist)
			{
				second_dist = dist;
				second_best = j;
			}
		}
		counter++;
		
		//insert point to its nearest cluster
		map[Points[i]] = Cluster_Table[cluster_pos];
		Info temp(Points[i],point_id[i],i,second_best,min_dist);
		cluster[cluster_pos]->InsertPoint(temp);
	}

	// std::cout <<"ASSIGNED "<<counter<<" elements"<<std::endl;
}

void LSH_Assignment(std::map<std::vector<double>, std::vector<double>>& map, HashTable** hashTables, Cluster **cluster, std::vector<std::vector<double>>& Points, std::vector<std::vector<double>>& Cluster_Table, std::vector<std::string>& point_id, int& k_lsh, int& L, int& w, bool& k_means_flag)
{
	//clean structure
	for (int i=0;i<Cluster_Table.size();i++)
	{
		cluster[i]->clear_structure();
	}
	// Search_Neighbors(cluster, Points, Cluster_Table, point_id, k_lsh, L, w);
	Search_Neighbors(map, hashTables, cluster, Points, Cluster_Table, point_id, k_lsh, L, w, k_means_flag);
}

void Hypercube_Assignment(std::map<std::vector<double>, std::vector<double>>& map, HashTable* hashTables, Cluster **cluster, std::vector<std::vector<double>>& Points, std::vector<std::vector<double>>& Cluster_Table, std::vector<std::string>& point_id, std::map<int, bool>& coinmap, int& k_cube, int& M, int& probes, int& w, bool& k_means_flag)
{
	//clean structure
	for (int i=0;i<Cluster_Table.size();i++)
	{
		cluster[i]->clear_structure();
	}
	// Search_Neighbors(cluster, Points, Cluster_Table, point_id, k_lsh, L, w);
	cube_Search_Neighbors(map, hashTables, cluster, Points, Cluster_Table, point_id, coinmap, k_cube, M, probes, w, k_means_flag);
}
