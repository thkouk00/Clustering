#include "../../include/Hypercube/NN_search.h"

using namespace std;

void NN_search(HashTable *cube, std::vector<int> &g, std::vector<double> &query, int &position, int &M, int &probes ,int &k, bool Euclidean, std::ofstream &output, double &ApproxDist, double &averagetime)
{
	int tmpfi;
	long double distance;

	std::vector<double> b;
	long double db = 9999999.0;
	string pid;
	
	bitset<32> hamming_distance;
	// initial hamming distance
	int h_dist = 1;
	bool neighbor_flag = 0;
	bool trick_used = 0;
	// points searched
	int count_lines=1;
	clock_t begin = clock();
	for (int i=0;i<probes;i++)
	{
		if (i > 1)
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
						
						// output <<"Initial position "<<position<<std::endl;
						position = tmp_pos;
						neighbor_flag = 1;
						// output <<"Position to neighbor vertex "<<position<<std::endl;
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
		
		for (std::list<Node>::iterator it = List.begin(); it!=List.end(); it++)
		{
		
			std::vector<double> p(it->get_p());
			
			if (Euclidean)
				distance = Euclidean_Distance(query,p);
			else
				distance = Cosine_Similarity(query,p);
		
			if (distance < db)
			{
				b = p;
				db = distance;
				pid = it->get_id();
			}
			
			//trick
			if (count_lines == M)
			{
				trick_used = 1;
				break;
			}
			count_lines++;	
		}
		if (trick_used)
			break;
	}
	clock_t end = clock();
	//measured in ms
	double elapsed_time = 1000 * ((double)(end-begin)/CLOCKS_PER_SEC);
	averagetime += elapsed_time;
	output <<"ANearest neighbor: "<<pid<<std::endl;
	output <<"distanceLSH: "<<db<<std::endl;
	ApproxDist = db;
	output <<"tLSH: "<<elapsed_time<<std::endl;
}