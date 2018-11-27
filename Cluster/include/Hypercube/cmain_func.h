#ifndef __CMAIN_FUNC_H__
#define __CMAIN_FUNC_H__
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <cmath>
#include <tgmath.h>
#include <vector>
#include <list>
#include <map>
#include "cube_general_functions.h"
#include "../cluster/Cluster.h"
#include "../LSH/HashTable.h"

void cube_Search_Neighbors(std::map<std::vector<double>, std::vector<double>>&, HashTable*, Cluster**, std::vector<std::vector<double>>&, std::vector<std::vector<double>>&, std::vector<std::string>&, std::map<int, bool>&, int&, int&, int&, int&, bool&);
void cube_Search_Neighbors(char*, char*, int&, int&, int&, int&);

#endif