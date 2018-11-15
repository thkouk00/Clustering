#include "../../include/cluster/Initialization.h"

using namespace std;


void Random_Initialization(std::vector<std::vector<double>>& Cluster_Table, std::vector<std::vector<double>>& Points,int& k)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator (seed);
	std::uniform_int_distribution<int> distribution(0,Points.size()-1);
	
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
				Cluster_Table.push_back(Points[rand_center]);
				break;
			}
		}
	}
}

void K_means_plusplus(std::vector<std::vector<double>>& Cluster_Table, std::vector<std::vector<double>>& Points, int& k)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator (seed);
	int points_size = Points.size();
	std::uniform_int_distribution<int> distribution(0,points_size-1);
	
	cout <<"Points_size "<<points_size<<std::endl;;
	int centroid = distribution(generator);	

	//holds position of clusters in points
	Cluster_Table.push_back(Points[centroid]);
	cout <<"FIRST CENTROID "<<centroid<<std::endl;

	//holds min dist for every Point
	std::vector<double> min_distance;
	std::vector<int> point_pos;
	std::vector<double> max_distance;
	std::vector<std::vector<double>>::iterator it;
	
	std::vector<double> P;
	//P[0] = 0.0;
	P.push_back(0);
	//loop until all centroids are collected
	for (int i=0;i<k-1;i++)
	{
		//for every point find min_distance
		for (int j=0;j<Points.size();j++)	
		{
			// current point is centroid
			it = find(Cluster_Table.begin(), Cluster_Table.end(), Points[j]);
			if (it != Cluster_Table.end())
				continue;

			double dist = Euclidean_Distance(Points[j], Points[centroid]);
			if ( point_pos.size() < Points.size()-Cluster_Table.size() )
			{
				point_pos.push_back(j);
				min_distance.push_back(dist);
				max_distance.push_back(dist);
			}
			else
			{
				if (min_distance[j] > dist)
					min_distance[j] = dist;
				
				if (max_distance[j] < dist)
					max_distance[j] = dist;
			}
		}

		for (int j=0;j<point_pos.size();j++)
		{
			double prob = 0;
			//partial sum for every element in vector
			for (int y=0;y<=j;y++)
				prob += pow(min_distance[y], 2);
			prob = prob / max_distance[j];
			P.push_back(P[j] + prob);
			cout <<P[j+1]<<std::endl;
		}
		cout <<"---------------------------------"<<std::endl;

		// std::uniform_real_distribution<double> distr(0,P[P.size()-1]);
		std::uniform_real_distribution<double> distr(0,P[Points.size()-Cluster_Table.size()]);
		double x = distr(generator);
		int upper = P.size();
		int lower = 1;
		int mid = lower + ((upper-lower)/2);
		cout <<"X is "<<x<<std::endl;
		cout <<"Mid before while "<<mid<<" upper "<<upper<<" and lower "<<lower<<std::endl;
		cout <<"Bound "<<P[Points.size()-Cluster_Table.size()]<<std::endl;;
		while(1)
		{
			if (P[mid] == x)
			{
				centroid = point_pos[mid-1];
				cout <<"NEW ELEMENT P[mid]==x -> "<<mid<<" and centroid "<<centroid<<std::endl;

				//delete centroid from  point vector
				point_pos.erase(point_pos.begin() + (mid - 1));
				min_distance.erase(min_distance.begin()+(mid - 1));
				max_distance.erase(max_distance.begin()+(mid - 1));
				
				break;
			}
			else if (P[mid] > x)
			{
				if (mid > 0 && P[mid-1] < x)
				{
					centroid = point_pos[mid-1];
					cout <<"NEW ELEMENT second case "<<mid<<" and centroid "<<centroid<<std::endl;
					
					//delete centroid from  point vector
					point_pos.erase(point_pos.begin() + (mid - 1));
					min_distance.erase(min_distance.begin()+(mid - 1));
					max_distance.erase(max_distance.begin()+(mid - 1));
					
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

				cout <<"New mid "<<mid<<" upper "<<upper<<" lower "<<lower<<std::endl;
			}	
		}
		Cluster_Table.push_back(Points[centroid]);
	}
	
	//print clusters to see the actual centroids
	for (int i=0;i<Cluster_Table.size();i++)
	{
		std::vector<double> v = Cluster_Table[i];
		for (int j=0;j<v.size();j++)
			cout <<v[j]<<' ';
		cout <<std::endl;
	}
}




// std::uniform_real_distribution<double> distr(0,P[P.size()-1]);
// double x = distr(generator);
// int upper = P.size();
// int lower = 1;
// int mid = lower + ((upper-lower)/2);
// cout <<"X is "<<x<<std::endl;
// cout <<"Mid before while "<<mid<<" upper "<<upper<<" and lower "<<lower<<std::endl;
// while(1)
// {
// 	if (P[mid] == x)
// 	{
// 		// centroid = mid;
// 		cout <<"NEW ELEMENT P[mid]==x -> "<<mid<<std::endl;
// 		centroid = point_pos[mid];
// 		break;
// 	}
// 	else if (P[mid] > x)
// 	{
// 		if (mid > 0 && P[mid-1] < x)
// 		{
// 			// centroid = mid;
// 			cout <<"NEW ELEMENT second case "<<mid<<std::endl;
// 			centroid = point_pos[mid];
// 			point_pos.erase(point_pos.begin() + mid);
// 			min_distance.erase(min_distance.begin()+mid);
// 			max_vec.erase(max_vec.begin()+mid);
// 			break;
// 		}	
// 		else
// 		{
// 			upper = mid;
// 			mid = lower + (upper-lower)/2; 
// 		}
// 	} 
// 	else
// 	{
// 		lower = mid;
// 		mid = lower + (upper-lower)/2; 
// 		if (mid == lower)
// 			mid++;

// 		cout <<"New mid "<<mid<<" upper "<<upper<<" lower "<<lower<<std::endl;
// 	}
// }