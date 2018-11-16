#include "../../include/cluster/Update.h"

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


void PAM_improved(Cluster **cluster, std::vector<std::vector<double>>& Points, std::vector<std::vector<double>>& Cluster_Table, std::vector<std::string>& point_id,bool& flag)
{
	cout <<"IN PAM CLSTER TABLE SIZE "<<Cluster_Table.size()<<std::endl;
	for (int i=0;i<Cluster_Table.size();i++)
	{
		//compute dist from old centroid
		double old_dist = 0;
		std::vector<Info> info_array;
		info_array = cluster[i]->get_array();
		//std::vector<double> old_centroid = Cluster_Table[i];
		for (int j=0;j<info_array.size();j++)
			old_dist += info_array[j].get_distance();

		// int temp_center;
		double distance = 0;
		double min_dist = old_dist;
		int min_index = -1;
		std::vector<double> temp_point;
		for (int j=0;j<info_array.size();j++)
		{
			distance = info_array[j].get_distance();
			// temp_center = j;
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
		// cluster[i]->set_clusterPoint(info_array[min_index].get_point());
		cout <<"PRINT NEW CENTER"<<std::endl;
		cout <<"MIN INDEX "<<min_index<<std::endl;
		cout <<"ARRAY SIZE "<<info_array.size()<<std::endl;
		if (min_index != -1)
		{
			cout <<std::endl;
			cout <<"----CLUSTER BEFORE----"<<std::endl;
			for (int y=0;y<Cluster_Table[i].size();y++)
				cout <<Cluster_Table[i][y]<<' ';
			cout <<std::endl;
			Cluster_Table[i] = info_array[min_index].get_point();
			cout <<"----CLUSTER AFTER----"<<std::endl;
			for (int y=0;y<Cluster_Table[i].size();y++)
				cout <<Cluster_Table[i][y]<<' ';
			cout <<std::endl;
			cout <<std::endl;
			flag = 0;
		}
	}
	
}

void k_means(Cluster **cluster, std::vector<std::vector<double>>& Points, std::vector<std::vector<double>>& Cluster_Table, std::vector<std::string>& point_id)
{
	// for (int i=0;i<Cluster_Table.size();i++)
	// {

	// 	// Info info;
	// 	int size = cluster[i]->get_ClusterSize();
	// 	//initialize result vector with zeros
	// 	std::vector<double> result(Points[0].size());
	// 	std::vector<Info> info_array;
	// 	info_array = cluster[i]->get_array();
	// 	// get every point in cluster
	// 	for (int j=0;j<info_array.size();j++)
	// 	{
	// 		std::vector<double> point = info_array[j].get_point();
	// 		result = add_vectors(result, point);
	// 	}
	// 	//upologise kai to kentro
	// 	result = add_vectors(result, Cluster_Table[i]); 
	// 	result = calculate_average(result,info_array.size());
		
	// 	//xreiazetai na valw to palio kentro san geitona??
	// 	// if (cluster[i]->get_cluster_id() != -1)
	// 	// {

	// 	// }
		
	// 	int pos;
	// 	std::vector<std::vector<double>>::iterator it;
	// 	it = find(Points.begin(), Points.end(), result);
	// 	if (it != Points.end())
	// 	{
	// 		pos = it - Points.begin();
	// 		cluster[i]->set_clusterId(pos);
	// 	}
	// 	else
	// 	{
	// 		pos = -1; 
	// 		cluster[i]->set_clusterId(pos);	
	// 	}

	// 	cluster[i]->set_clusterPoint(result);
	// }
}