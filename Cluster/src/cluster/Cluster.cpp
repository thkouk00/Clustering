#include "../../include/cluster/Cluster.h"

Cluster::Cluster(){};
Cluster::~Cluster(){};

void Cluster::InsertPoint(Info point)
{
	this->Array.push_back(point);
}

int Cluster::get_ClusterSize()
{
	return this->Array.size();
}

std::vector<Info> Cluster::get_array()
{
	return this->Array;
}

void Cluster::clear_structure()
{
	this->Array.clear();
}


void MapNode::set_info(int cluster, int second_best, double Rad, double dist)
{
	this->cluster_pos = cluster;
	this->second_best = second_best;
	this->Radius = Rad;
	this->distance = dist;
}
void MapNode::get_all(int& cluster_pos, int& second_best, double& rad, double& distance)
{

	cluster_pos = this->cluster_pos;
	second_best = this->second_best;
	rad = this->Radius; 
	distance = this->distance; 
}