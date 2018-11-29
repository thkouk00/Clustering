#ifndef __CLUSTERH__
#define __CLUSTERH__
#include <iostream>
#include <list>
#include <vector>
#include "Point_Info.h"

class Cluster
{
	std::vector<Info> Array; 

public:
	Cluster();
	~Cluster();
	void InsertPoint(Info);
	int get_ClusterSize();
	std::vector<Info> get_array();
	int get_cluster_id();
	void set_clusterPoint(std::vector<double>);
	void clear_structure();
};

class MapNode
{
	int cluster_pos;
	int second_best;
	double Radius;
	double distance;
	
public:
	MapNode(){};
	~MapNode(){};
	void set_info(int, int, double, double);
	void get_all(int&, int&, double&, double&);
};

#endif