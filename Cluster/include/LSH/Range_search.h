#ifndef _RANGE_SEARCH_H_
#define _RANGE_SEARCH_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <map>
#include <string.h>
#include <stdlib.h>
#include <ctime>
// #include "../include/HashTable.h"
#include "HashTable.h"
#include "Buckets.h"
#include "Distance.h"
#include "../cluster/Cluster.h"

//LSH Clustering
void Range_search(std::map<std::vector<double>, MapNode>&, HashTable**, std::vector<std::vector<int>> &, std::vector<double> &, std::vector<std::vector<double>>&, std::vector<int> &, int &, int &, double &, bool, bool&, int&);
//Euclidean and Cosine
void Range_search(HashTable **, std::vector<std::vector<int>>&, std::vector<double>&, std::vector<int>&, int &, int &, double&, bool, double&);

#endif