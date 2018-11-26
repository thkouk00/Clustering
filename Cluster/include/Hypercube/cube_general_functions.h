#ifndef _GENERAL_FUNCTIONS_H_
#define _GENERAL_FUNCTIONS_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <cmath>
#include <bits/stdc++.h>
#include "cube_Range_search.h"
#include "../LSH/normal_distr.h"
#include "../LSH/HashTable.h"
#include "../cluster/Cluster.h"

void cube_storeDataset(std::vector<std::vector<double>>&, std::vector<std::string>&,char *, int&, bool &, double &);

void cube_search_neighbors(std::map<std::vector<double>, MapNode>&, HashTable*, std::vector<std::string>&, std::vector<std::vector<double>>&, std::map<int,bool>&, int&, int&, int&, int&, int&, bool&);
// void cube_search_neighbors(cube_HashTable *, std::vector<std::string>&, std::vector<std::vector<double>>&, std::map<int,bool>&, int&, int&, int&, int&, int&, double&, bool&);
int cube_find_hashFunction(std::vector<int>&, std::vector<double> &, std::map<int,bool>&, int&, int&, int&, int&, bool);

#endif