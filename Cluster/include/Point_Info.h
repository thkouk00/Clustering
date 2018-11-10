#ifndef __POINTINFOH__
#define __POINTINFOH__
#include <iostream>
#include <vector>
#include <list>


class Info
{
	std::vector<double>& Point;
	std::string Point_id;
	int second_best_cluster;
public:
	Info(std::vector<double>&, std::string, int);
	// Info(){};
	~Info(){};
	
};

#endif