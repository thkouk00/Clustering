#ifndef __POINTINFOH__
#define __POINTINFOH__
#include <iostream>
#include <vector>
#include <list>


class Info
{
	std::vector<double>& Point;
	std::string Point_id;
	int Pos_id;
	int second_best_cluster;
	double distance;
public:
	Info(std::vector<double>&, std::string, int, int, double);
	Info();
	~Info(){};
	std::vector<double>& get_point();
	double get_distance();
	int get_Pos_Id();
	std::string get_Point_Id();
	void set_point();
	void set_distance();
	void clear_info();
};

#endif