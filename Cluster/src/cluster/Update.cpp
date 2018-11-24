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

double calculate_objectiveFunc(std::vector<double>& pointA, std::vector<Info>& Array)
{
	long double value = 0;
	for (int j=0;j<Array.size();j++)
	{
		std::vector<double> pointB = Array[j].get_point();
		if (pointA == pointB)
			continue;
		double dist = Euclidean_Distance(pointA, pointB);
		value += dist;
	}

	return value;
}

void PAM_improved(Cluster **cluster, std::vector<std::vector<double>>& Points, std::vector<std::vector<double>>& Cluster_Table, std::vector<std::string>& point_id,bool& flag)
{
	int changes = 0;
	for (int i=0;i<Cluster_Table.size();i++)
	{
		int new_centroid = -1;
		double min_objValue = -1;
		std::vector<Info> Array = cluster[i]->get_array();
		// calculate current objective function value
		std::vector<double> current_centroid = Cluster_Table[i];
		double old_objValue = calculate_objectiveFunc(current_centroid, Array);
		for (int j=0;j<Array.size();j++)
		{
			std::vector<double> point = Array[j].get_point();
			double tmp_objFunc_val = calculate_objectiveFunc(point,Array);
			tmp_objFunc_val += Euclidean_Distance(point, Cluster_Table[i]);
			if (j == 0)
			{
				min_objValue = tmp_objFunc_val;
				new_centroid = j;
			}
			else if (min_objValue > tmp_objFunc_val)
			{
				min_objValue = tmp_objFunc_val;
				new_centroid = j;
			}
		}
		cout <<"Old objVal "<<old_objValue<<std::endl;
		cout <<"New objVal "<<min_objValue<<std::endl;
		if (min_objValue < old_objValue && min_objValue != -1)
		{
			Cluster_Table[i] = Array[new_centroid].get_point();
			changes++;
		}
		
	}
	cout <<"****CHANGES "<<changes<<" ****"<<std::endl;
	if (changes == 0 || ((changes*100)/Cluster_Table.size()) <= 15) //|| (((changes*100)/Cluster_Table.size()) <= 10 && Cluster_Table.size() >= 50))
	{
		cout <<"POSOSTO "<<(changes*100)/(double)Cluster_Table.size()<<std::endl;
		flag = 0;
	}
	
}

// void PAM_improved(Cluster **cluster, std::vector<std::vector<double>>& Points, std::vector<std::vector<double>>& Cluster_Table, std::vector<std::string>& point_id,bool& flag)
// {
// 	// std::vector<std::vector<double>> New_Cluster_Table(Cluster_Table.size());
// 	// std::vector<std::vector<double>>::iterator it;
// 	int changes = 0;
// 	cout <<"IN PAM CLSTER TABLE SIZE "<<Cluster_Table.size()<<std::endl;
// 	for (int i=0;i<Cluster_Table.size();i++)
// 	{
// 		//compute dist from old centroid
// 		double old_dist = 0;
// 		std::vector<Info> info_array;
// 		info_array = cluster[i]->get_array();
// 		// empty cluster
// 		if (info_array.size() == 0)
// 			continue;
// 		cout <<"Cluster i= "<<i<<" has "<<info_array.size()<<" points"<<std::endl;
// 		for (int j=0;j<info_array.size();j++)
// 			old_dist += info_array[j].get_distance();

// 		// int temp_center;
// 		// double distance = 0;
// 		double min_dist = old_dist;
// 		// double min_dist = 0;
// 		int min_index = -1;
// 		std::vector<double> temp_centroid;
// 		for (int j=0;j<info_array.size();j++)
// 		{
// 			double distance = 0;
// 			// dist from centroid
// 			// distance = info_array[j].get_distance();
// 			// temp_center = j;
// 			temp_centroid = info_array[j].get_point();
// 			for (int y=0;y<info_array.size();y++)
// 			{
// 				std::vector<double> tpoint = info_array[y].get_point() ;
// 				if (temp_centroid == tpoint)
// 				// if (j == y)
// 					continue;
// 				distance += Euclidean_Distance(temp_centroid,tpoint);
// 			}

// 			if (min_dist > distance)
// 			{
// 				min_dist = distance;
// 				min_index = j;
// 			}
// 		}
// 		//update new centroid
// 		cout <<"PRINT NEW CENTER"<<std::endl;
// 		cout <<"MIN INDEX "<<min_index<<std::endl;
// 		cout <<"ARRAY SIZE "<<info_array.size()<<std::endl;
// 		// min_index == -1 means that  new_centroid == old_centroid
// 		if (min_index != -1)
// 		{
			
// 			Cluster_Table[i] = info_array[min_index].get_point();
// 			changes++;

// 			cout <<"Cluster "<<i<<" allaxe kentro se "<<min_index<<std::endl;
// 			temp_centroid = info_array[min_index].get_point(); 
// 			for (int n=0;n<temp_centroid.size();n++)
// 				cout <<temp_centroid[n]<<' ';
// 			cout <<std::endl;
// 		}
// 		else
// 		{
// 			// flag = 0;
// 			cout <<"Palio kentro paramenei"<<std::endl;
// 		}
// 	}
	
// 	// if (changes >=2 )
// 	double percentage = (changes*100)/(double)(Cluster_Table.size());
// 	cout <<"Pososto allagis "<<percentage<<std::endl;
// 	if (percentage <= 20)
// 		flag = 0;
	
// }

void k_means(Cluster **cluster, std::vector<std::vector<double>>& Points, std::vector<std::vector<double>>& Cluster_Table, std::vector<std::string>& point_id)
{
	for (int i=0;i<Cluster_Table.size();i++)
	{

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
		
		Cluster_Table[i] = result;
	}
}