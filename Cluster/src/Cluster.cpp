#include "../include/Cluster.h"

void Cluster::InsertPoint(Info point)
{
	this->Array.push_back(point);
}

int Cluster::get_ClusterSize()
{
	return this->Array.size();
}

void Cluster::set_clusterPoint(std::vector<double> point)
{
	this->cluster_point = point;
}

std::vector<Info>& Cluster::get_array()
{
	return this->Array;
}