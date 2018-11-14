#include "../../include/LSH/Node.h"
using namespace std;

Node::Node(string str,vector<double> &v,std::vector<int> g):id(str),p(v),g(g)
{
	
}

void Node::printPoints()
{
	cout <<"Id: "<<this->id<<std::endl;
	for (vector<double>::iterator it=p.begin();it!=p.end();it++)
		cout <<*it<<" ";
	cout <<endl;
}

std::vector<double>& Node::get_p()
{
	return this->p;
}

std::vector<int> Node::get_g()
{
	return this->g;
}

std::string Node::get_id()
{
	return this->id;
}