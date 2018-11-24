#ifndef _NN_SEARCH_H_
#define _NN_SEARCH_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <string.h>
#include <stdlib.h>
#include <chrono>
#include "HashTable.h"
#include "Buckets.h"
#include "Distance.h"

void NN_search(HashTable *cube, std::vector<int> &g, std::vector<double> &query, int &position, int &M, int &probes, int &k, bool Cosine, std::ofstream &output, double&, double&);

#endif