#include "../../include/cluster/Assignment.h"

void Lloyds_Assignment(Cluster **cluster, std::vector<std::vector<double>>& Points, std::vector<std::vector<double>>& Cluster_Table, std::vector<std::string>& point_id)
{

	//clean structure
	for (int i=0;i<Cluster_Table.size();i++)
	{
		cluster[i]->clear_structure();
		std::vector<Info> v = cluster[i]->get_array();
		std::cout <<"SSIZEARRAY "<<v.size()<<" and Cluster "<<Cluster_Table[i].size()<<std::endl;
	}

	double dist;
	int cluster_pos;
	int second_cluster;
	for (int i=0;i<Points.size();i++)
	{
		double min_dist = 9999999;
		double second_best = 9999999;
		
		//check if point is centroid
		std::vector<std::vector<double>>::iterator it;
		it = find(Cluster_Table.begin(), Cluster_Table.end(), Points[i]);
		if (it != Cluster_Table.end())
			continue;
		
		for (int j=0;j<Cluster_Table.size();j++)
		{
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

void LSH_Assignment(Cluster **cluster, std::vector<std::vector<double>>& Points, std::vector<std::vector<double>>& Cluster_Table, std::vector<std::string>& point_id, int& k_lsh, int& L, int& w)
{
	//clean structure
	for (int i=0;i<Cluster_Table.size();i++)
	{
		cluster[i]->clear_structure();
	}
	// Search_Neighbors(cluster, Points, Cluster_Table, point_id, k_lsh, L, w);
	Search_Neighbors(cluster, Points, Cluster_Table, point_id, k_lsh, L, w);
}
