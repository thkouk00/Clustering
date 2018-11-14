#ifndef __MAIN_FUNC_H__
#define __MAIN_FUNC_H__
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include "../include/HashTable.h"
#include "../include/general_functions.h"
#include "../../include/Cluster.h"

void Search_Neighbors(Cluster**, std::vector<std::vector<double>>&, std::vector<std::vector<double>>&, std::vector<std::string>&, int&, int&, int&);
void Search_Neighbors(char*, char*, int&, int&, int&);

#endif