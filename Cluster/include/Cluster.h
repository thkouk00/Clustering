#ifndef __CLUSTERH__
#define __CLUSTERH__
#include <iostream>
#include <list>
#include <vector>
#include "../include/Point_Info.h"

class Cluster
{
	std::vector<Info> Array; 
	int Cluster_id;

public:
	Cluster(int id)
	{
		this->Cluster_id = id;
	};
	~Cluster(){};
	void InsertPoint(Info);
};

#endif