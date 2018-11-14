#ifndef _NN_SEARCH_H_
#define _NN_SEARCH_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <string.h>
#include <stdlib.h>
#include "HashTable.h"
#include "Buckets.h"
#include "Distance.h"

void NN_search(HashTable **hashTables, std::vector<std::vector<int>> &g, std::vector<double> &query, std::vector<int> &fi, int &L, int &k, bool Cosine, std::ofstream &output,double &, double&);

#endif