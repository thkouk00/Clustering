#ifndef __UPDATE_H__
#define __UPDATE_H__
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>    // std::find
#include "Cluster.h"
#include "Point_Info.h"
#include "../LSH/Distance.h"

std::vector<double> add_vectors(std::vector<double>&, std::vector<double>&);
std::vector<double> calculate_average(std::vector<double>&, int);
double calculate_objectiveFunc(std::vector<double>&, std::vector<Info>&, int&);

void PAM_improved(Cluster **, std::vector<std::vector<double>>&, std::vector<std::vector<double>>&, std::vector<std::string>&, bool&);
void k_means(Cluster **, std::vector<std::vector<double>>&, std::vector<std::vector<double>>&, std::vector<std::string>&);


#endif