#include "../../include/LSH/NN_search.h"
#include "../../include/LSH/Range_search.h"

using namespace std;

void NN_search(HashTable **hashTables, std::vector<std::vector<int>> &g, std::vector<double> &query, std::vector<int> &fi, int &L, int &k, bool Euclidean, std::ofstream &output, double &ApproxDist, double &averagetime)
{
	int tmpfi;
	long double distance;
	std::vector<double> b;
	long double db = 9999999.0;
	string pid;

	clock_t begin = clock();
	for (int i=0;i<L;i++)
	{
		tmpfi = fi[i];
		std::vector<int> tmpg(g[i]);
		if (!(hashTables[i]->bucket_exist(tmpfi)))
			continue;

		Buckets* bucket = hashTables[i]->access_bucket(tmpfi);
		if (bucket == NULL)
			continue;
		
		list<Node> List = bucket->access_list();
		int count_lines=1;
		for (std::list<Node>::iterator it = List.begin(); it!=List.end(); it++)
		{
			std::vector<double> p(it->get_p());
			if (Euclidean)
			{
				// check if gs are same
				std::vector<int> pq(it->get_g());
				if (tmpg != pq)
				{
					//paralipsi ++lines ??
					continue;
				}
				distance = Euclidean_Distance(query,p);
			}
			else
				distance = 1 - Cosine_Similarity(query,p);
			
			if (distance < db)
			{
				b = p;
				db = distance;
				pid = it->get_id();
			}
			
			//trick
			if (count_lines == 3*L)
			{
				break;
			}
			count_lines++;	
		}
	}
	clock_t end = clock();
	// measured in ms
	double elapsed_time = 1000* ((double)(end-begin)/CLOCKS_PER_SEC);
	averagetime += elapsed_time;
	
	output <<"ANearest neighbor: "<<pid<<std::endl;
	output <<"distanceLSH: "<<db<<std::endl;
	ApproxDist = db;
	output <<"tLSH: "<<elapsed_time<<std::endl;
}