#include "../../include/LSH/Buckets.h"

using namespace std;

Buckets::Buckets(string str,vector<double> &v,vector<int> g)
{
	Node node(str,v,g);
	this->List.push_back(node);
}

void Buckets::insertPointAtList(string str,vector<double> &v,vector<int> g)
{
	Node node(str,v,g);
	this->List.push_back(node);
}

void Buckets::printList()
{
	for (list<Node>::iterator it=List.begin();it!=this->List.end();it++)
		it->printPoints();
}

int Buckets::bucket_size()
{
	return this->List.size();
}

std::list<Node> Buckets::access_list()
{
	return this->List;
}