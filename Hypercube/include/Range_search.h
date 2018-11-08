#ifndef _RANGE_SEARCH_H_
#define _RANGE_SEARCH_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <string.h>
#include <stdlib.h>
#include <chrono>
#include "../include/HashTable.h"
#include "../include/Buckets.h"
#include "../include/Distance.h"

// void Range_search(HashTable *, std::vector<int>&, std::vector<double>&, int&, int&, int &, int &, double&, bool, std::ofstream&, double&);
void Range_search(HashTable *, std::vector<int>&, std::vector<double>&, int&, int&, int &, int &, double&, bool, double&);

#endif