#include "../../include/cluster/Silhouette.h"

using namespace std;

extern std::vector<std::vector<double>> Distance_Table;
extern std::vector<int> Cluster_position;
extern bool metric;

//evaluate clustering
double Silhouette(std::vector<std::vector<double>>& Cluster_Table, Cluster** cluster, int& number_of_clusters, bool& k_means_flag, std::ofstream& outputfile)
{
	bool flag = 0;
	double silhouette_value = 0;
	for (int i=0;i<number_of_clusters;i++)
	{
		double cluster_value = 0;
		std::vector<Info> Array = cluster[i]->get_array();
		
		if (Array.size() == 0)
			continue;
		for (int j=0;j<Array.size();j++)
		{
			Info object = Array[j];
			double s;
			double a = 0;
			double b = 0;
			
			if (Array.size() > 0)
			{
				a = avg_dist_sameCluster(object, Array, k_means_flag);
				b = avg_dist_neighbor(object, cluster, k_means_flag);
				if (b == 0)
					continue;
				
				cluster_value += (b-a)/std::max(a,b);
			}
		}
		if (Array.size() != 0)
		{
			double val = cluster_value/Array.size();
			silhouette_value += val;
			outputfile <<val<<", ";
		}
	}
	
	silhouette_value = silhouette_value/number_of_clusters;
	outputfile <<silhouette_value<<std::endl;

	return silhouette_value;
}

//average distance of i to other objects in same cluster
double avg_dist_sameCluster(Info& current_obj, std::vector<Info>& Array, bool& k_means_flag)
{
	std::vector<Info>::iterator it;
	double dist = 0;
	std::vector<double> pointA = current_obj.get_point();
	int pointA_pos = current_obj.get_Pos_Id();
	if (Array.size() == 1)
		return 0;
	for (int i=0;i<Array.size();i++)
	{
		Info object = Array[i];
		std::vector<double> pointB = object.get_point();
		int pointB_pos = object.get_Pos_Id();

		if (pointA == pointB)
			continue;

		if (!k_means_flag)
			dist += Find_Distance(pointA, pointB, pointA_pos, pointB_pos);		
		else
		{
			if (metric == 1)
				dist += Euclidean_Distance(pointA, pointB);
			else
				dist += 1 - Cosine_Similarity(pointA, pointB);
		}
	}
	dist = dist/(Array.size() - 1);
	return dist;
}

// average distance of i to objects in next best (neighbor) cluster
double avg_dist_neighbor(Info& current_obj, Cluster** cluster, bool& k_means_flag)
{
	double dist = 0;
	std::vector<double> pointA = current_obj.get_point();
	
	// for (int i=0;i<pointA.size();i++)
	// 	cout <<pointA[i]<<' ';
	// cout <<std::endl;
	
	int pointA_pos = current_obj.get_Pos_Id();
	int sec_best = current_obj.get_secondBestCluster();
	if (sec_best == -1)
		return 0;
	
	std::vector<Info> Array = cluster[current_obj.get_secondBestCluster()]->get_array();
	
	if (Array.size() == 0)
		return 0;
	
	for (int i=0;i<Array.size();i++)
	{
		Info object = Array[i];
		std::vector<double> pointB = object.get_point();
		int pointB_pos = object.get_Pos_Id();

		if (!k_means_flag)
			dist += Find_Distance(pointA, pointB, pointA_pos, pointB_pos);
		else
		{
			if (metric == 1)
				dist += Euclidean_Distance(pointA, pointB);
			else
				dist += 1 - Cosine_Similarity(pointA, pointB);	
		}

	}
	dist = dist/(Array.size());
	
	return dist;
}