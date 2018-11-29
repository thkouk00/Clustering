#include "../../include/Hypercube/cube_Range_search.h"

using namespace std;

extern bool metric;

// void Range_search(HashTable *cube, std::vector<int> &g, std::vector<double> &query, int &position, int &M, int &probes, int &k, double &R, bool Euclidean, std::ofstream &output, double &TrueDist)
void cube_Range_search(std::map<std::vector<double>, MapNode>& assigned_elements, HashTable *cube, std::vector<int> &g, std::vector<double> &query, std::vector<std::vector<double>> &queryset, int &position, int &M, int &probes, int &k, double &R, bool Euclidean, bool& Stop, int& cluster_pos)
{
	int tmpfi;
	long double distance;
	long double db = 9999999.0;
	std::vector<double> b;
	string pid;
	
	std::map<std::vector<double>, MapNode>::iterator mapIt;

	bitset<32> hamming_distance;
	// initial hamming distance
	int h_dist = 1;
	bool neighbor_flag = 0;
	// clock_t begin = clock();
	for (int i=0;i<probes;i++)
	{
		if (i >= 1)
			break;
		if (i != 0)
		{
			int y;
			int tmp_pos;
			while (!neighbor_flag)
			{
				bitset<32> current_vertex(position);
				for (y=0;y<cube->get_num_of_buckets();y++)
				{
					if (y == position)
						continue;
					bitset<32> neighbor(y);
					hamming_distance = current_vertex ^ neighbor;
					// find new bucket position
					if (hamming_distance.count() == h_dist)
					{
						tmp_pos = (int)(neighbor.to_ulong());
						
						if (!(cube->bucket_exist(tmp_pos)))
							continue;
						
						position = tmp_pos;
						neighbor_flag = 1;
						break;
					}
				}
				// if no neighbor with hamming distance h_dist , search for h_dist+1
				if (y == cube->get_num_of_buckets() && !neighbor_flag)
					h_dist++;
			}
		}
		if (!(cube->bucket_exist(position)))
			continue;
		Buckets* bucket = cube->access_bucket(position);
		if (bucket == NULL)
			continue;
		list<Node> List = bucket->access_list();
		
		std::vector<std::vector<double>>::iterator Qit;
		for (std::list<Node>::iterator it = List.begin(); it!=List.end(); it++)
		{
			std::vector<double> p(it->get_p());
			
			// metric = 1 euclidean , metric = 0 cosine
			if (metric == 1)
				distance = Euclidean_Distance(query,p);
			else
				distance = Cosine_Similarity(query,p);

			// trueNN
			// if (distance < db)
			// {
			// 	b = p;
			// 	db = distance;
			// 	pid = it->get_id();
			// }
			
			if (R != 0)
			{
				//range 
				if (distance < R)
				{
					MapNode tempNode;
					mapIt = assigned_elements.find(p);
					if (mapIt != assigned_elements.end())
					{
						int assigned_cluster;
						int second_best;
						double assigned_dist;
						double assigned_radius;
						tempNode = mapIt->second;
						tempNode.get_all(assigned_cluster, second_best, assigned_radius, assigned_dist);
						if (assigned_cluster != cluster_pos)
						{
							if (assigned_radius == R)
							{
								if (assigned_dist > distance)
								{
									second_best = assigned_cluster;

									assigned_dist = distance;
									assigned_cluster = cluster_pos;
									if (Stop)
										Stop = 0;
								}
							}
							else if (assigned_radius > R)
							{
								second_best = assigned_cluster;

								assigned_dist = distance;
								assigned_cluster = cluster_pos;
								if (Stop)
									Stop = 0;
							}
						}
					}
					else
					{
						int temp_sec = -1;
						tempNode.set_info(cluster_pos, temp_sec, R, distance);
						assigned_elements[p] = tempNode;
						if (Stop)
							Stop = 0;
					}
				}
			}
		}
	}
}