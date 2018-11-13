#ifndef __POINTINFOH__
#define __POINTINFOH__
#include <iostream>
#include <vector>
#include <list>


class Info
{
	std::vector<double>& Point;
	std::string Point_id;
	double distance;
	int second_best_cluster;
public:
	Info(std::vector<double>&, std::string, double, int);
	// Info(){};
	~Info(){};
	std::vector<double>& get_point();
	double get_distance();
	void set_point();
	void set_distance();
};

#endif