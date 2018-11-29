#ifndef __MAIN_FUNC_H__
#define __MAIN_FUNC_H__

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <chrono>
#include "../../include/cluster/Cluster.h"
#include "../../include/cluster/Initialization.h"
#include "../../include/cluster/Assignment.h"
#include "../../include/cluster/Update.h"
#include "../../include/cluster/Silhouette.h"
#include "../../include/LSH/HashTable.h"
#include "../../include/Hypercube/cube_HashTable.h"

void cluster_main_func(std::vector<std::vector<double>>&, std::vector<std::string>& id, std::string, int&, int&, int&, int&, int&, int&, int&, bool&);

#endif