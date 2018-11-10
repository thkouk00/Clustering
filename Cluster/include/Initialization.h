#ifndef __INITIALIZATION_H__
#define __INITIALIZATION_H__
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>	//seed 
#include <algorithm> //find
#include <math.h>	//pow
#include "../LSH/include/Distance.h"

void Random_Initialization(int&, int&, std::vector<int>&);
void K_means_plusplus(int&, int&, std::vector<int>&, std::vector<std::vector<double>>&);

#endif