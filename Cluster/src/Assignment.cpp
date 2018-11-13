#include "../include/Assignment.h"

void Lloyds_Assignment(Cluster **cluster, std::vector<std::vector<double>>& Points, std::vector<std::vector<double>>& Cluster_Table, std::vector<std::string>& point_id)
{

	//clean structure
	for (int i=0;i<Cluster_Table.size();i++)
	{
		cluster[i]->clear_structure();
	}

	double dist;
	int cluster_pos;
	int second_cluster;
	for (int i=0;i<Points.size();i++)
	{
		double min_dist = 9999999;
		double second_best = 9999999;
		
		for (int j=0;j<Cluster_Table.size();j++)
		{
			if (Points[i] == Cluster_Table[j])
				break;
			// dist = Euclidean_Distance(Points[i], Points[Cluster_Table[j]]);
			dist = Euclidean_Distance(Points[i], Cluster_Table[j]);
			if (min_dist > dist)
			{
				second_best = min_dist;
				min_dist = dist;
				second_cluster = cluster_pos;
				cluster_pos = j;
			}
			else if (second_best > dist)
			{
				second_best = dist;
				second_cluster = j;
			}
		} 
		Info temp(Points[i],point_id[i],i,second_cluster,min_dist);
		cluster[cluster_pos]->InsertPoint(temp);
	}
}

void LSH_Assignment(Cluster **cluster, std::vector<std::vector<double>>& Points, std::vector<std::string>& point_id, std::vector<int>& Cluster_Table, int& k, int& L, int& w)
{
	char* input_file, *query_file;
	Search_Neighbors(input_file, query_file, k, L, w);
}
