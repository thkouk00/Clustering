#include "../../include/cluster/Assignment.h"

using namespace std;

void Lloyds_Assignment(std::map<std::vector<double>, std::vector<double>>& map, Cluster **cluster, std::vector<std::vector<double>>& Points, std::vector<std::vector<double>>& Cluster_Table, std::vector<std::string>& point_id, bool& k_means_flag)
{
	for (int i=0;i<Cluster_Table.size();i++)
		cluster[i]->clear_structure();
	
	// counter gia diki moy xrisi na vlepw posa shmeia kanei assign
	int counter = 0;
	std::vector<std::vector<double>>::iterator it;
	for (int i=0;i<Points.size();i++)
	{
		int cluster_pos = -1;
		int second_best = -1;
		double min_dist = 0;
		double second_dist = 999999;
		// check if Point[i] is centroid
		it = find(Cluster_Table.begin(),Cluster_Table.end(),Points[i]);
		// Point is centroid
		if (it != Cluster_Table.end())
			continue;

		for (int j=0;j<Cluster_Table.size();j++)
		{
			double dist = Euclidean_Distance(Points[i], Cluster_Table[j]);
			if (j == 0)
			{
				min_dist = dist;
				cluster_pos = j;
			}
			else if (min_dist > dist)
			{
				// update second best cluster
				cout <<"Allagi kentroy apo cluster "<<cluster_pos<<" me "<<min_dist<<" se kentro "<<j<<" me "<<dist<<std::endl;
				second_dist = min_dist;
				second_best = cluster_pos;
				// update new cluster position
				min_dist = dist;
				cluster_pos = j;
			}
			else if (second_dist > dist)
			{
				second_dist = dist;
				second_best = j;
			}
		}
		counter++;
		//exei brethei to kontinotero cluster
		map[Points[i]] = Cluster_Table[cluster_pos];
		cout <<"Point "<<i+1<<" Cluster "<<cluster_pos<<" Second best "<<second_best<<std::endl;
		Info temp(Points[i],point_id[i],i,second_best,min_dist);
		cout <<"Inserting in cluster "<<cluster_pos<<std::endl;
		cluster[cluster_pos]->InsertPoint(temp);
	}

	std::cout <<"ASSIGNED "<<counter<<" elements"<<std::endl;
}

// void Lloyds_Assignment(std::map<std::vector<double>, std::vector<double>>& map, Cluster **cluster, std::vector<std::vector<double>>& Points, std::vector<std::vector<double>>& Cluster_Table, std::vector<std::string>& point_id, bool& k_means_flag)
// {

// 	//clean structure
// 	for (int i=0;i<Cluster_Table.size();i++)
// 	{
// 		cluster[i]->clear_structure();
// 		std::vector<Info> v = cluster[i]->get_array();
// 		// std::cout <<"SSIZEARRAY "<<v.size()<<" and Cluster "<<Cluster_Table[i].size()<<std::endl;
// 	}


// 	int counter = 0;
// 	double dist;
// 	int cluster_pos = -1;
// 	int second_cluster;
// 	for (int i=0;i<Points.size();i++)
// 	{
// 		double min_dist = 9999999;
// 		double second_best = 9999999;
		
// 		//check if point is centroid
// 		std::vector<std::vector<double>>::iterator it;
// 		it = find(Cluster_Table.begin(), Cluster_Table.end(), Points[i]);
// 		if (it != Cluster_Table.end())
// 		{
// 			std::cout <<"EURIKA position "<<i<<" k="<<Cluster_Table.size()<<std::endl;
// 			continue;
// 		}
		
// 		for (int j=0;j<Cluster_Table.size();j++)
// 		{
// 			dist = Euclidean_Distance(Points[i], Cluster_Table[j]);
// 			if (min_dist > dist)
// 			{
// 				//at first iteration second best cluster is itself
// 				if (cluster_pos == -1)
// 					cluster_pos = j;
				
// 				second_best = min_dist;
// 				second_cluster = cluster_pos;
// 				min_dist = dist;
// 				cluster_pos = j;
// 			}
// 			else if (second_best > dist)
// 			{
// 				second_best = dist;
// 				second_cluster = j;
// 			}
// 		} 
// 		// std::cout <<"Second Best cluster for cluster "<<i<<" is "<<second_cluster<<std::endl;
// 		Info temp(Points[i],point_id[i],i,second_cluster,min_dist);
// 		cluster[cluster_pos]->InsertPoint(temp);
// 		counter++;
// 		if (k_means_flag)
// 			map[Points[i]] = Cluster_Table[cluster_pos];
// 	}
// 	std::cout <<"ASSIGNED "<<counter<<" elements"<<std::endl;
// }

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
