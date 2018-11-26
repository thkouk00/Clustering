#ifndef _RANGE_SEARCH_H_
#define _RANGE_SEARCH_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <string.h>
#include <stdlib.h>
#include <chrono>
#include "../LSH/Buckets.h"
#include "../LSH/Distance.h"
#include "../LSH/HashTable.h"
#include "../cluster/Cluster.h"

// void Range_search(HashTable *, std::vector<int>&, std::vector<double>&, int&, int&, int &, int &, double&, bool, std::ofstream&, double&);
// void cube_Range_search(std::map<std::vector<double>, MapNode>&, cube_HashTable *, std::vector<int>&, std::vector<double>&, std::vector<std::vector<double>>&, int&, int&, int &, int &, double&, bool, double&);
void cube_Range_search(std::map<std::vector<double>, MapNode>&, HashTable*, std::vector<int>&, std::vector<double>&, std::vector<std::vector<double>>&, int&, int&, int&, int&, double&, bool, bool&, int&);
#endif