#include "../../include/cluster/Initialization.h"

using namespace std;


void Random_Initialization(Cluster **cluster, std::vector<std::vector<double>>& Points,int& k, int& num_of_lines)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator (seed);
	std::uniform_int_distribution<int> distribution(0,num_of_lines-1);
	
	std::vector<int> vec;	
	std::vector<int>::iterator it;

	int rand_center = -1;
	for (int i=0;i<k;i++)
	{
		while (1)
		{
			rand_center = distribution(generator);
			
			//every element must be unique
			it = find(vec.begin(), vec.end(), rand_center);
			if (it != vec.end())
			{
				cout <<"Element already exists in vec "<<*it<<std::endl;
				continue;
			}
			else
			{
				cout <<"new element "<<rand_center<<std::endl;
				vec.push_back(rand_center);
				cluster[i]->set_clusterPoint(Points[rand_center]);
				cluster[i]->set_clusterId(rand_center);
				break;
			}
		}
	}
}

void K_means_plusplus(Cluster **cluster, std::vector<std::vector<double>>& Points, int& k, int& num_of_lines)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator (seed);
	std::uniform_int_distribution<int> distribution(0,num_of_lines-1);
	
	int centroid = distribution(generator);
	std::vector<std::vector<double>> centers;	

	//holds position of clusters in points
	centers.push_back(Points[centroid]);
	// Cluster_Table.push_back(centroid);

	//holds min dist for every Point
	std::vector<double> min_distance;
	std::vector<int> point_pos;
	std::vector<int> id;
	//loop until all centroids are collected
	for (int i=0;i<k-1;i++)
	{
		id.push_back(centroid);
		double dist;
		double max_dist = -1;
		std::vector<double> P;
		//for every point loop to find min dist among every cluster
		for (int j=0;j<num_of_lines;j++)
		{
			if(j == 0)
				P.push_back(0.0);

			bool flag = 0;
			for (int y=0; y<centers.size(); y++)
			{
				//if Point[j] is center go to next loop
				if (Points[j] == centers[y])
				{
					flag = 1;
					break;
				}
			}
			//Point is centroid
			if (flag)
				continue;

			//find dist between point and cluster , store min dist only
			dist = Euclidean_Distance(Points[j], Points[centroid]);
			if (i==0)
				min_distance.push_back(dist);
			else if (min_distance[j] > dist)
				min_distance[j] = dist;		
			//store max_dist in order to normalize result
			if (max_dist < dist)
				max_dist = dist;

			//store position of elements that have been examined
			point_pos.push_back(j);
			double prob = 0;
			//calculate partial sums
			for (int y = 0; y<point_pos.size();y++)
			{
				prob += pow(min_distance[y],2)/max_dist; 
			}
			P[j+1] = prob;
		
		}
		// //calculate every point's probability in order to be new centroid
		// for (int j=1; j<=num_of_lines; j++)
		// {
		// 	P[j] += pow(min_distance[j],2);
		// 	// double prob = P[j] + (pow(min_distance[j], 2)/pow(max_dist, 2));
		// 	// P.push_back(prob);
		// }

		//find new centroid using binary search
		std::uniform_int_distribution<int> distr(0,P[P.size()-1]);
		double x = distr(generator);
		int upper = P.size();
		int lower = 1;
		int mid = lower + (upper-lower)/2;
		while(1)
		{
			if (P[mid] == x)
			{
				// centroid = mid;
				centroid = point_pos[mid];
				break;
			}
			else if (P[mid] > x)
			{
				if (mid > 0 && P[mid-1] < x)
				{
					// centroid = mid;
					centroid = point_pos[mid];
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
		centers.push_back(Points[centroid]);
		// Cluster_Table.push_back(centroid);
	}

	for (int i=0;i<k;i++)
	{
		cluster[i]->set_clusterPoint(centers[i]);
		cluster[i]->set_clusterId(id[i]);
	}
	//print clusters to see the actual centroids
}