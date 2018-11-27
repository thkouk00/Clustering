#ifndef __ASSIGNMENT_H__
#define __ASSIGNMENT_H__
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Cluster.h"
#include "Point_Info.h"
#include "../LSH/Distance.h"
#include "../LSH/main_func.h"
#include "../Hypercube/cmain_func.h"

// void Lloyds_Assignment(Cluster **, std::vector<std::vector<double>>&, std::vector<std::vector<double>>&, std::vector<std::string>&);
// void LSH_Assignment(HashTable**, Cluster **, std::vector<std::vector<double>>&, std::vector<std::vector<double>>&, std::vector<std::string>&, int&, int&, int&);

//for k_means,  track if there is change in assignments
void Lloyds_Assignment(std::map<std::vector<double>, std::vector<double>>&, Cluster **, std::vector<std::vector<double>>&, std::vector<std::vector<double>>&, std::vector<std::string>&, bool&, double&);
void LSH_Assignment(std::map<std::vector<double>, std::vector<double>>&, HashTable**, Cluster **, std::vector<std::vector<double>>&, std::vector<std::vector<double>>&, std::vector<std::string>&, int&, int&, int&, bool&);
void Hypercube_Assignment(std::map<std::vector<double>, std::vector<double>>&, HashTable*, Cluster**, std::vector<std::vector<double>>&, std::vector<std::vector<double>>&, std::vector<std::string>&, std::map<int, bool>&, int&, int&, int&, int&, bool&);

#endif