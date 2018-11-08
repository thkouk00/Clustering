#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include <vector>
#include <string>

class Node
{
	// id int or string
	std::string id;
	std::vector<double> &p;
	std::vector<int> g;

public:
	Node(std::string,std::vector<double>&,std::vector<int>);
	~Node(){};
	void printPoints();
	std::vector<double>& get_p();
	std::vector<int> get_g();
	std::string get_id();
	
};

#endif
