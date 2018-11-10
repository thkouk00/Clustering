#include "../include/Assignment.h"

void Lloyds_Assignment(Cluster **cluster, std::vector<std::vector<double>>& Points, std::vector<std::string>& point_id,std::vector<int>& Cluster_Table)
{
	double dist;
	int cluster_id;
	int second_cluster;
	for (int i=0;i<Points.size();i++)
	{
		double min_dist = 9999999;
		double second_best = 9999999;
		
		for (int j=0;j<Cluster_Table.size();j++)
		{
			if (Points[i] == Points[j])
				break;
			dist = Euclidean_Distance(Points[i], Points[Cluster_Table[j]]);
			if (min_dist > dist)
			{
				second_best = min_dist;
				min_dist = dist;
				second_cluster = cluster_id;
				cluster_id = Cluster_Table[j];
			}
			else if (second_best > dist)
			{
				second_best = dist;
				second_cluster = Cluster_Table[j];
			}
		} 
		Info temp(Points[i],point_id[i],second_cluster);
		cluster[cluster_id]->InsertPoint(temp);
	}
}

void LSH_Assignment(Cluster **cluster, std::vector<std::vector<double>>& Points, std::vector<std::string>& point_id, std::vector<int>& Cluster_Table, int& k, int& L, int& w)
{
	char* input_file, *query_file;
	Search_Neighbors(input_file, query_file, k, L, w);
}