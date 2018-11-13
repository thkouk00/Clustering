#include "../include/Point_Info.h"

Info::Info(std::vector<double>& point, std::string id, double dist, int second_best): Point(point), Point_id(id), distance(dist), second_best_cluster(second_best)
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