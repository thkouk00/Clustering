#ifndef __SILHOUETTEH__
#define __SILHOUETTEH__

#include <iostream>
#include <vector>
#include "Cluster.h"
#include "../LSH/Distance.h"

double Silhouette(Cluster**, int&);
double avg_dist_sameCluster(Info&, std::vector<Info>&);
double avg_dist_neighbor(Info&, Cluster**);

#endif