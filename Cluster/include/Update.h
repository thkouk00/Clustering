#ifndef __UPDATE_H__
#define __UPDATE_H__
#include <iostream>
#include <list>
#include <vector>
#include "../include/Cluster.h"
#include "../LSH/include/Distance.h"


void k_means(Cluster **, std::vector<std::vector<double>>&, std::vector<std::string>&, std::vector<int>&);
void PAM_improved(Cluster **, std::vector<std::vector<double>>&, std::vector<std::string>&, std::vector<int>&);

std::vector<double> add_vectors(std::vector<double>&, std::vector<double>&);
std::vector<double> calculate_average(std::vector<double>&, int);

#endif