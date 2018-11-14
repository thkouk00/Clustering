#ifndef _GENERAL_FUNCTIONS_H_
#define _GENERAL_FUNCTIONS_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <cmath>
#include <bits/stdc++.h>
#include "HashTable.h"
#include "normal_distr.h"
#include "NN_search.h"
#include "Range_search.h"
#include "../cluster/Cluster.h"

void storeDataset(std::vector<std::vector<double>>&, std::vector<std::string>&,char *, int&, bool &, double &);
void search_neighbors(std::map<std::vector<double>, MapNode>&, HashTable**, std::vector<std::string>&, std::vector<std::vector<double>>&, int&, int&, int&, int&, bool);
// void search_neighbors(HashTable **, std::vector<std::string> &, std::vector<std::vector<double>>&, int&, int&, int&, int&, double&,bool,std::ofstream&);
void search_neighbors(HashTable **, std::vector<std::string> &, std::vector<std::vector<double>>&, int&, int&, int&, int&, double&,bool);
int find_hashFunction(std::vector<int>&, std::vector<double> &, int&, int&, int&, int&, bool);

#endif