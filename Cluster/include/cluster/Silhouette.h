#ifndef __SILHOUETTEH__
#define __SILHOUETTEH__

#include <iostream>
#include <vector>
#include "Cluster.h"
#include <fstream>
#include <sstream>
#include "../LSH/Distance.h"

double Silhouette(std::vector<std::vector<double>>&, Cluster**, int&, bool&, std::ofstream&);
double calc_distance(std::vector<double>&, Cluster**, int);
double avg_dist_sameCluster(Info&, std::vector<Info>&, bool&);
double avg_dist_neighbor(Info&, Cluster**, bool&);

#endif