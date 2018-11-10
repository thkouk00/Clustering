#ifndef __ASSIGNMENT_H__
#define __ASSIGNMENT_H__
#include <iostream>
#include <vector>
#include <string>
#include "../LSH/include/Distance.h"
#include "../include/Cluster.h"
#include "../include/Point_Info.h"
#include "../LSH/include/main_func.h"

void Lloyds_Assignment(Cluster**, std::vector<std::vector<double>>&, std::vector<std::string>&, std::vector<int>&);
void LSH_Assignment(Cluster**, std::vector<std::vector<double>>&, std::vector<std::string>&, std::vector<int>&, int&, int&, int&);
void Hypercube_Assignment();


#endif