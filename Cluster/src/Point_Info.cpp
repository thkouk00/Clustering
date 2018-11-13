#include "../include/Point_Info.h"

Info::Info(std::vector<double>& point, std::string id, int pos_id,int second_best, double dist): Point(point), Point_id(id), Pos_id(pos_id), second_best_cluster(second_best), distance(dist)
{

}

std::vector<double>& Info::get_point()
{
	return this->Point;
}

double Info::get_distance()
{
	return this->distance;
}

int Info::get_Pos_Id()
{
	return this->Pos_id;
}

std::string Info::get_Point_Id()
{
	return this->Point_id;
}

void Info::clear_info()
{
	this->Point.clear();
	this->Point_id.clear();
	this->Pos_id = -1;
	this->second_best_cluster = -1;
	this->distance = -1;
}