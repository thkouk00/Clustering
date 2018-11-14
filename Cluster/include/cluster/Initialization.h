#ifndef __INITIALIZATION_H__
#define __INITIALIZATION_H__
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>	//seed 
#include <algorithm> //find
#include <math.h>	//pow
#include "Cluster.h"
#include "../LSH/Distance.h"

void Random_Initialization(Cluster **, std::vector<std::vector<double>>&, int&, int&);
void K_means_plusplus(Cluster **, std::vector<std::vector<double>>&, int&, int&);

#endif