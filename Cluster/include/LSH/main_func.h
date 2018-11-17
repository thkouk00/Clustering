#ifndef __MAIN_FUNC_H__
#define __MAIN_FUNC_H__
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include "HashTable.h"
#include "general_functions.h"
#include "../cluster/Cluster.h"

void Search_Neighbors(std::map<std::vector<double>, std::vector<double>>&, HashTable**, Cluster**, std::vector<std::vector<double>>&, std::vector<std::vector<double>>&, std::vector<std::string>&, int&, int&, int&, bool&);
void Search_Neighbors(char*, char*, int&, int&, int&);

#endif