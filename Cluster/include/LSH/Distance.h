#ifndef _DISTANCE_H_
#define _DISTANCE_H_

#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

long double Euclidean_Distance(std::vector<double>&, std::vector<double>&);
long double Cosine_Similarity(std::vector<double>&, std::vector<double>&);

double Find_Distance(std::vector<double>&, std::vector<double>&, int&, int&);

#endif