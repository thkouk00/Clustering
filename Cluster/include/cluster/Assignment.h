#ifndef __ASSIGNMENT_H__
#define __ASSIGNMENT_H__
#include <iostream>
#include <vector>
#include <string>
#include "Cluster.h"
#include "Point_Info.h"
#include "../LSH/Distance.h"
#include "../LSH/main_func.h"

void Lloyds_Assignment(Cluster **, std::vector<std::vector<double>>&, std::vector<std::vector<double>>&, std::vector<std::string>&);
void LSH_Assignment(Cluster **, std::vector<std::vector<double>>&, std::vector<std::vector<double>>&, std::vector<std::string>&, double&, int&, int&, int&);
void Hypercube_Assignment();


#endif