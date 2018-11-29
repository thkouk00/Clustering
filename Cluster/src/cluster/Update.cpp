#include "../../include/cluster/Update.h"

using namespace std;

extern std::vector<std::vector<double>> Distance_Table;
extern std::vector<int> Cluster_position;

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

double calculate_objectiveFunc(std::vector<double>& pointA, std::vector<Info>& Array, int& pointA_position)
{
	long double value = 0;
	// if (Array.size() == 0)
	// 	cout <<"Empty Cluster"<<std::endl;
	for (int j=0;j<Array.size();j++)
	{
		std::vector<double> pointB = Array[j].get_point();
		if (pointA == pointB)
			continue;
		int pointB_position = Array[j].get_Pos_Id();
		// value += Euclidean_Distance(pointA, pointB);
		value += Find_Distance(pointA, pointB, pointA_position, pointB_position);
	}

	if (value == 0)
		value = -1;

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
		// if (Array.size() == 0)
		// 	continue;
		
		double old_objValue = calculate_objectiveFunc(current_centroid, Array, Cluster_position[i]);
		for (int j=0;j<Array.size();j++)
		{
			std::vector<double> point = Array[j].get_point();
			if (point == Cluster_Table[i])
				continue;
			int point_position = Array[j].get_Pos_Id();
			double tmp_objFunc_val = calculate_objectiveFunc(point, Array, point_position);
	
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
		if (min_objValue < old_objValue && min_objValue != -1)
		{
			Cluster_Table[i] = Array[new_centroid].get_point();
			Cluster_position[i] = Array[new_centroid].get_Pos_Id();
			changes++;
		}	
	}

	if (changes == 0 )//|| ((changes*100)/Cluster_Table.size()) <= 15) //|| (((changes*100)/Cluster_Table.size()) <= 10 && Cluster_Table.size() >= 50))
		flag = 0;
	
}

void k_means(Cluster **cluster, std::vector<std::vector<double>>& Points, std::vector<std::vector<double>>& Cluster_Table, std::vector<std::string>& point_id)
{
	for (int i=0;i<Cluster_Table.size();i++)
	{

		//initialize result vector with zeros
		std::vector<double> result(Points[0].size());
		std::vector<Info> info_array = cluster[i]->get_array();
		
		// get every point in cluster
		if (info_array.size() == 0)
			continue;
		for (int j=0;j<info_array.size();j++)
		{
			std::vector<double> point = info_array[j].get_point();
			result = add_vectors(result, point);
		}
		
		result = calculate_average(result,info_array.size());
		
		Cluster_Table[i] = result;
	}
}