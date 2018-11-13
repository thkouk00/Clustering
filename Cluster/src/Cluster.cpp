#include "../include/Cluster.h"

void Cluster::InsertPoint(Info point)
{
	this->Array.push_back(point);
}

int Cluster::get_ClusterSize()
{
	return this->Array.size();
}

double Cluster::get_minDist()
{
	return this->min_dist;
}

std::vector<Info>& Cluster::get_array()
{
	return this->Array;
}

int Cluster::get_cluster_id()
{
	return this->Cluster_id;
}

void Cluster::set_clusterPoint(std::vector<double> point)
{
	this->cluster_point = point;
}

void Cluster::set_clusterId(int& id)
{
	this->Cluster_id = id;
}

void Cluster::set_info(std::vector<double> point, int id, double dist)
{
	this->cluster_point = point;
	this->Cluster_id = id;
	this->min_dist = dist;
}

void Cluster::clear_structure()
{
	for (int i=0;i<this->Array.size();i++)
	{
		(this->Array[i]).clear_info();
	}
	this->Cluster_id = -1;
	this->cluster_point.clear();
}