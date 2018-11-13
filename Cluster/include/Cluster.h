#ifndef __CLUSTERH__
#define __CLUSTERH__
#include <iostream>
#include <list>
#include <vector>
#include "../include/Point_Info.h"

class Cluster
{
	std::vector<Info> Array; 
	std::vector<double> cluster_point;
	int Cluster_id;

public:
	Cluster(int id)
	{
		this->Cluster_id = id;
	};
	~Cluster(){};
	void InsertPoint(Info);
	int get_ClusterSize();
	void set_clusterPoint(std::vector<double>);
	std::vector<Info>& get_array();
};

#endif