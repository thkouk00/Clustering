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
#include "../include/HashTable.h"
#include "../include/normal_distr.h"
#include "../include/NN_search.h"
#include "../include/Range_search.h"
#include "../../include/Cluster.h"

void storeDataset(std::vector<std::vector<double>>&, std::vector<std::string>&,char *, int&, bool &, double &);
void search_neighbors(Cluster**, HashTable**, std::vector<std::string>&, std::vector<std::vector<double>>&, int&, int&, int&, int&, double&,bool);
// void search_neighbors(HashTable **, std::vector<std::string> &, std::vector<std::vector<double>>&, int&, int&, int&, int&, double&,bool,std::ofstream&);
void search_neighbors(HashTable **, std::vector<std::string> &, std::vector<std::vector<double>>&, int&, int&, int&, int&, double&,bool);
int find_hashFunction(std::vector<int>&, std::vector<double> &, int&, int&, int&, int&, bool);

#endif