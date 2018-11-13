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
	// -1 if point not in dataset, else id == Position in Points vector
	int Cluster_id;
	double min_dist;

public:
	Cluster(int id)
	{
		this->Cluster_id = id;
	};
	Cluster();
	~Cluster(){};
	void InsertPoint(Info);
	int get_ClusterSize();
	double get_minDist();
	std::vector<Info>& get_array();
	int get_cluster_id();
	void set_clusterPoint(std::vector<double>);
	void set_clusterId(int&);
	void set_info(std::vector<double>, int, double);
	void clear_structure();
};

#endif