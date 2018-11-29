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
		std::cout <<"SIl ARRAY SIZE "<<Array.size()<<std::endl;
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
				// cout <<"Before a"<<std::endl;
				a = avg_dist_sameCluster(object, Array, k_means_flag);
				// cout <<"After a "<<a<<" and before b"<<std::endl;
				b = avg_dist_neighbor(object, cluster, k_means_flag);
				// cout <<"after b "<<b<<std::endl;
				cout <<"A is "<<a<<" and B is "<<b<<std::endl;
				if (b == 0)
					continue;
				// 	flag = 1;
				// else
				cluster_value += (b-a)/std::max(a,b);
				// cout <<"A is "<<a<<" B is "<<b<<" result "<<(b-a)/std::max(a,b)<<std::endl;
			}
		}
		if (Array.size() != 0)
		{
			double val = cluster_value/Array.size();
			silhouette_value += val;
			cout <<"Sill "<<silhouette_value<<std::endl;
			cout <<"Cluster val"<<cluster_value<<" and array size "<<Array.size()<<std::endl;
			outputfile <<val<<", ";
		}
	}
	// if (flag)
	// {
	// 	cout <<"***Wrong Clustering...Empty clusters-Try different k***"<<std::endl;
	// 	silhouette_value = silhouette_value/number_of_clusters;
	// 	// silhouette_value = -1;
	// }
	// else
	silhouette_value = silhouette_value/number_of_clusters;
	outputfile <<silhouette_value<<std::endl;

	return silhouette_value;
}

//average distance of i to other objects in same cluster
double avg_dist_sameCluster(Info& current_obj, std::vector<Info>& Array, bool& k_means_flag)
{
	cout <<"Ypologismos A"<<std::endl;
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
				dist += Cosine_Similarity(pointA, pointB);
		}
	}
	dist = dist/(Array.size() - 1);
	return dist;
}

// average distance of i to objects in next best (neighbor) cluster
double avg_dist_neighbor(Info& current_obj, Cluster** cluster, bool& k_means_flag)
{
	cout <<"Ypologismos B"<<std::endl;
	// cout <<"MPIKA"<<std::endl;
	double dist = 0;
	std::vector<double> pointA = current_obj.get_point();
	// cout <<"PointA is ";
	for (int i=0;i<pointA.size();i++)
		cout <<pointA[i]<<' ';
	cout <<std::endl;
	// cout <<"PIRA POINT "<<current_obj.get_secondBestCluster()<<std::endl;
	// for (int i=0;i<Cluster_position.size();i++)
	// {
	// 	if (current_obj.get_secondBestCluster() == Cluster_position[i])
	// 	{
	// 		Array = cluster[i]->get_array();
	// 		break;
	// 	}
	// }
	// cout <<"Array size "<<Array.size()<<std::endl;
	int pointA_pos = current_obj.get_Pos_Id();
	int sec_best = current_obj.get_secondBestCluster();
	if (sec_best == -1)
		return 0;
	
	std::vector<Info> Array = cluster[current_obj.get_secondBestCluster()]->get_array();
	cout <<"****Array SIZe "<<Array.size()<<std::endl;
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
				dist += Cosine_Similarity(pointA, pointB);	
		}

	}
	dist = dist/(Array.size());
	
	return dist;
}