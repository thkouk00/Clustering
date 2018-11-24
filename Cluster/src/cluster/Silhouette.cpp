#include "../../include/cluster/Silhouette.h"

using namespace std;

//evaluate clustering
double Silhouette(Cluster** cluster, int& number_of_clusters)
{
	bool flag = 0;
	double silhouette_value = 0;
	for (int i=0;i<number_of_clusters;i++)
	{
		double cluster_value = 0;
		std::vector<Info> Array = cluster[i]->get_array();
		std::cout <<"SIl ARRAY SIZE "<<Array.size()<<std::endl;
		for (int j=0;j<Array.size();j++)
		{
			Info object = Array[j];
			double s;
			double a = 0;
			double b = 0;
			
			if (Array.size() != 1)
			{
				a = avg_dist_sameCluster(object, Array);
				b = avg_dist_neighbor(object, cluster);
				if (b == 0)
					flag = 1;
				else
					cluster_value += (b-a)/std::max(a,b);
				// cout <<"A is "<<a<<" B is "<<b<<" result "<<(b-a)/std::max(a,b)<<std::endl;
			}
			// else
			// 	cluster_value = 0;
		}
		if (Array.size() != 0)
			silhouette_value += cluster_value/Array.size();
	}
	if (flag)
	{
		cout <<"***Wrong Clustering...Empty clusters-Try different k***"<<std::endl;
		silhouette_value = silhouette_value/number_of_clusters;
		// silhouette_value = -1;
	}
	else
		silhouette_value = silhouette_value/number_of_clusters;

	return silhouette_value;
}

//average distance of i to other objects in same cluster
double avg_dist_sameCluster(Info& current_obj, std::vector<Info>& Array)
{
	std::vector<Info>::iterator it;
	double dist = 0;
	for (int i=0;i<Array.size();i++)
	{
		Info object = Array[i];
		std::vector<double> pointA = current_obj.get_point();
		std::vector<double> pointB = object.get_point();

		if (pointA == pointB)
			continue;

		dist += Euclidean_Distance(pointA, pointB);		
	}
	dist = dist/(Array.size() - 1);
	return dist;
}

// average distance of i to objects in next best (neighbor) cluster
double avg_dist_neighbor(Info& current_obj, Cluster** cluster)
{
	double dist = 0;
	std::vector<double> pointA = current_obj.get_point();
	std::vector<Info> Array = cluster[current_obj.get_secondBestCluster()]->get_array();
	if (Array.size() == 0)
		return 0;
	for (int i=0;i<Array.size();i++)
	{
		Info object = Array[i];
		std::vector<double> pointB = object.get_point();

		dist += Euclidean_Distance(pointA, pointB);	
	}
	dist = dist/(Array.size());
	
	return dist;
}