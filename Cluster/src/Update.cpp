#include "../include/Update.h"

using namespace std;

std::vector<double> calculate_average(std::vector<double>& A, int size)
{
	std::vector<double> result;
	for (int i=0;i<A.size();i++)
	{
		result.push_back(A[i]/size);
	}
	return result;
}

std::vector<double> add_vectors(std::vector<double>& A, std::vector<double>& B)
{
	if (A.size() != B.size())
	{
		cout <<"Vectors of different size, cant calculate average"<<std::endl;
		exit(1);
 	}
 	std::vector<double> result;
 	int size = A.size();
 	for (int i=0;i<size;i++)
 	{
 		result.push_back(A[i]+B[i]);
 	}
 	return result;
}


void PAM_improved(Cluster **cluster, std::vector<std::vector<double>>& Points, std::vector<std::string>& point_id,std::vector<int>& Cluster_Table)
{
	for (int i=0;i<Cluster_Table.size();i++)
	{
		//compute dist from old centroid
		double old_dist = 0;
		std::vector<Info> info_array;
		info_array = cluster[i]->get_array();
		for (int j=0;j<info_array.size();j++)
			old_dist += info_array[j].get_distance();

		int temp_center;
		double distance = 0;
		double min_dist = old_dist;
		int min_index;
		std::vector<double> temp_point;
		for (int j=0;j<info_array.size();j++)
		{
			distance = info_array[j].get_distance();
			temp_center = j;
			temp_point = info_array[j].get_point();
			for (int y=0;y<info_array.size();y++)
			{
				std::vector<double> tpoint = info_array[y].get_point() ;
				if (temp_point == tpoint)
					continue;
				distance += Euclidean_Distance(temp_point,tpoint);
			}

			if (min_dist > distance)
			{
				min_dist = distance;
				min_index = j;
			}
		}
		//update new centroid
		cluster[i]->set_clusterPoint(info_array[min_index].get_point());
		//prpei na valw to palio centroid stous geitones
		//kai thn apostash toy apo to new centroid
		//na xanadw thn domh info ti perilamvanei
		// info_array[min_index].set
	}
	
}

void k_means(Cluster **cluster, std::vector<std::vector<double>>& Points, std::vector<std::string>& point_id,std::vector<int>& Cluster_Table)
{
	for (int i=0;i<Cluster_Table.size();i++)
	{

		// Info info;
		int size = cluster[i]->get_ClusterSize();
		//initialize result vector with zeros
		std::vector<double> result(Points[0].size());
		std::vector<Info> info_array;
		info_array = cluster[i]->get_array();
		// get every point in cluster
		for (int j=0;j<info_array.size();j++)
		{
			std::vector<double> point = info_array[j].get_point();
			result = add_vectors(result, point);
		}
		result = calculate_average(result,info_array.size());
		cluster[i]->set_clusterPoint(result);
	}
}