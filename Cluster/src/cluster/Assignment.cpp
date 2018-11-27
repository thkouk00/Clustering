#include "../../include/cluster/Assignment.h"

using namespace std;

extern std::vector<std::vector<double>> Distance_Table;
extern std::vector<int> Cluster_position;

void Lloyds_Assignment(std::map<std::vector<double>, std::vector<double>>& map, Cluster **cluster, std::vector<std::vector<double>>& Points, std::vector<std::vector<double>>& Cluster_Table, std::vector<std::string>& point_id, bool& k_means_flag,double& objective)
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
		// it = find(Cluster_Table.begin(),Cluster_Table.end(),Points[i]);
		// // Point is centroid
		// if (it != Cluster_Table.end())
		// {
		// 	cout <<"EEW"<<std::endl;
		// 	map[Points[i]] = *it;
		// 	for (int j =0 ; j<Cluster_Table.size(); j++)
		// 	{
		// 		if (*it == Cluster_Table[j])
		// 		{
		// 			cluster_pos = j;
		// 			continue;
		// 		}
		// 		double 	tmp_dist = Find_Distance(Points[i], Cluster_Table[j], i, Cluster_position[j]);
		// 		if (second_dist > tmp_dist)
		// 		{
		// 			second_dist = tmp_dist;
		// 			second_best = j;
		// 		}	
		// 	}
		// 	min_dist = 0;
		// 	cout <<"EEW2"<<std::endl;
		// 	Info temp(Points[i],point_id[i],i,second_best,min_dist);
		// 	cluster[cluster_pos]->InsertPoint(temp);
		// 	continue;
		// }

		for (int j=0;j<Cluster_Table.size();j++)
		{
			double dist;
			if (!k_means_flag)
				dist = Find_Distance(Points[i], Cluster_Table[j], i, Cluster_position[j]);
			else
				dist = Euclidean_Distance(Points[i], Cluster_Table[j]);
			
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
			else if (second_dist > dist && dist != min_dist)
			{
				cout <<"*Allagi second best apo cluster "<<second_best<<" me "<<second_dist<<" se kentro "<<j<<" me "<<dist<<" me min_dist "<<min_dist<<std::endl;
				second_dist = dist;
				second_best = j;
			}
			if (Points[i] == Cluster_Table[j])
			{
				cout <<"---Cluster kai Point idia cluster number = "<<j<<" antistoixei sto Point_shmeio "<<Cluster_position[j]<<" kai point number = "<<i<<std::endl;
			}
		}
		counter++;
		// objective += pow(min_dist,2);
		//exei brethei to kontinotero cluster
		cout <<"Actual Point "<<i+1<<" Cluster "<<cluster_pos<<" Second best "<<second_best<<std::endl;
		map[Points[i]] = Cluster_Table[cluster_pos];
		Info temp(Points[i],point_id[i],i,second_best,min_dist);
		cout <<"Inserting in cluster "<<cluster_pos<<std::endl;
		cluster[cluster_pos]->InsertPoint(temp);
	}

	std::cout <<"ASSIGNED "<<counter<<" elements"<<std::endl;
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
