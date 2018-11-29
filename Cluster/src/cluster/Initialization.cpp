#include "../../include/cluster/Initialization.h"

using namespace std;

extern std::vector<std::vector<double>> Distance_Table;
// extern std::vector<int> Cluster_position;
extern std::vector<int> tmp_Cluster_position;

void Random_Initialization(std::vector<std::vector<double>>& Cluster_Table, std::vector<std::vector<double>>& Points,int& k)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator (seed);
	std::uniform_int_distribution<int> distribution(0,Points.size()-1);
	
	std::vector<int> vec;	
	std::vector<int>::iterator it;

	int rand_center;
	for (int i=0;i<k;i++)
	{
		while (1)
		{
			rand_center = distribution(generator);
			
			//every element must be unique
			it = find(vec.begin(), vec.end(), rand_center);
			if (it != vec.end())
			{
				// cout <<"Element already exists in vec "<<*it<<std::endl;
				continue;
			}
			else
			{
				vec.push_back(rand_center);
				Cluster_Table.push_back(Points[rand_center]);
				tmp_Cluster_position.push_back(rand_center);
				break;
			}
		}
	}
}

void K_means_plusplus(std::vector<std::vector<double>>& Cluster_Table, std::vector<std::vector<double>>& Points, int& k)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator (seed);
	
	std::uniform_int_distribution<int> distribution(0,Points.size()-1);
	
	int centroid = distribution(generator);	

	//holds position of clusters in points
	Cluster_Table.push_back(Points[centroid]);
	// cout <<"FIRST CENTROID "<<centroid<<std::endl;

	//holds min dist for every Point
	std::vector<int> point_pos;
	std::vector<double> min_distance;
	double max_distance;
	std::vector<std::vector<double>>::iterator it;
	
	std::vector<double> P;
	//loop until all centroids are collected
	for (int i=0;i<k-1;i++)
	{
		P.push_back(0);
		//for every point find min_distance
		for (int j=0;j<Points.size();j++)	
		{
			// current point is centroid
			it = find(Cluster_Table.begin(), Cluster_Table.end(), Points[j]);
			if (it != Cluster_Table.end())
				continue;

			double dist = Find_Distance(Points[j], Points[centroid], j, centroid);
			if (i == 0)
			{
				point_pos.push_back(j);
				min_distance.push_back(dist);
				max_distance = dist;
			}
			else
			{
				if (min_distance[j] > dist)
					min_distance[j] = dist;
				else if (max_distance < dist)
					max_distance = dist;
			}
		}

		for (int j=0;j<point_pos.size();j++)
		{
			//partial sum for every element in vector
			P.push_back(P[j] + ((min_distance[j]/max_distance)*(min_distance[j]/max_distance)));
		}

		std::uniform_real_distribution<double> distr(0,P[P.size()-1]);
		double x = distr(generator);
		int upper = P.size();
		int lower = 1;
		int mid = lower + ((upper-lower)/2);
		
		while(1)
		{
			if (P[mid] == x)
			{
				centroid = point_pos[mid-1];
				break;
			}
			else if (P[mid] > x)
			{
				if (mid > 0 && P[mid-1] < x)
				{
					centroid = point_pos[mid-1];
					break;
				}	
				else
				{
					upper = mid;
					mid = lower + (upper-lower)/2; 
				}
			} 
			else
			{
				lower = mid;
				mid = lower + (upper-lower)/2; 
				if (mid == lower)
					mid++;
			}	
		}
		point_pos.erase(point_pos.begin() + (mid - 1));
		min_distance.erase(min_distance.begin()+(mid - 1));
		Cluster_Table.push_back(Points[centroid]);
		tmp_Cluster_position.push_back(centroid);
		P.clear();
	}
}