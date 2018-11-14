#include "../include/Range_search.h"
using namespace std;

void Range_search(std::map<std::vector<double>, MapNode>& assigned_elements, HashTable **hashTables, std::vector<std::vector<int>> &g, std::vector<double> &query, std::vector<int> &fi, int &L, int &k, double &R, bool Euclidean, bool& Stop, int& cluster_pos)
{
	int tmpfi;
	long double distance;
	long double db = 9999999.0;
	std::vector<double> b;
	string pid;

	// output <<"R-near neighbors:"<<std::endl;
	cout <<"R-near neighbors:"<<std::endl;

	std::map<std::vector<double>, MapNode>::iterator mapIt;

	// clock_t begin = clock();
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
		for (std::list<Node>::iterator it = List.begin(); it!=List.end(); it++)
		{
			bool g_flag = 1;
			std::vector<double> p(it->get_p());  
			
			if (Euclidean)
			{
				// find distance for trueNN_neighbor
				distance = Euclidean_Distance(query,p);
				std::vector<int> pq(it->get_g());
				// check if g(q) and q(p) are same for Range_search
				// if g's are different -> flag = 0 else flag = 1
				if (tmpg != pq)
					g_flag = 0;
					// continue;
			}
			else
			{
				distance = Cosine_Similarity(query,p);
				g_flag = 1;
			}

			//trueNN
			// if (distance < db)
			// {
			// 	b = p;
			// 	db = distance;
			// 	pid = it->get_id();
			// }
			
			if (g_flag)
			{
				if (distance < R)
				{
					MapNode tempNode;
					mapIt = assigned_elements.find(p);
					if (mapIt != assigned_elements.end())
					{
						int assigned_cluster;
						double assigned_dist;
						double assigned_radius;
						tempNode = mapIt->second;
						tempNode.get_all(assigned_cluster, assigned_radius, assigned_dist);
						if (assigned_cluster != cluster_pos)
						{
							if (assigned_radius == R)
							{
								if (assigned_dist > distance)
								{
									assigned_dist = distance;
									assigned_cluster = cluster_pos;
									if (Stop)
										Stop = 0;
								}
							}
							else if (assigned_radius > R)
							{
								assigned_dist = distance;
								assigned_cluster = cluster_pos;
								if (Stop)
									Stop = 0;
							}
						}
					}
					else
					{
						tempNode.set_info(cluster_pos, R, distance);
						assigned_elements[p] = tempNode;
						if (Stop)
							Stop = 0;
					}
					cout <<it->get_id()<<" -> distance "<<distance<<std::endl;
				}
			}
		}
	}
}


//Euclidean and Cosine Metric
// void Range_search(HashTable **hashTables, std::vector<std::vector<int>> &g, std::vector<double> &query, std::vector<int> &fi, int &L, int &k, double &R, bool Euclidean, std::ofstream &output, double &TrueDist)
void Range_search(HashTable **hashTables, std::vector<std::vector<int>> &g, std::vector<double> &query, std::vector<int> &fi, int &L, int &k, double &R, bool Euclidean, double &TrueDist)
{
	int tmpfi;
	long double distance;
	long double db = 9999999.0;
	std::vector<double> b;
	string pid;

	// output <<"R-near neighbors:"<<std::endl;
	cout <<"R-near neighbors:"<<std::endl;

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
		for (std::list<Node>::iterator it = List.begin(); it!=List.end(); it++)
		{
			bool g_flag = 1;
			std::vector<double> p(it->get_p());  
			
			if (Euclidean)
			{
				// find distance for trueNN_neighbor
				distance = Euclidean_Distance(query,p);
				std::vector<int> pq(it->get_g());
				// check if g(q) and q(p) are same for Range_search
				// if g's different flag = 0, else flag = 1
				if (tmpg != pq)
					g_flag = 0;
					// continue;
			}
			else
			{
				distance = Cosine_Similarity(query,p);
				g_flag = 1;
			}

			//trueNN
			// if (distance < db)
			// {
			// 	b = p;
			// 	db = distance;
			// 	pid = it->get_id();
			// }
			
			if (g_flag)
			{
				if (distance < R)
				{
					// output <<it->get_id()<<" -> distance "<<distance<<std::endl;
					cout <<it->get_id()<<" -> distance "<<distance<<std::endl;
				}
			}
		}
	}
	clock_t end = clock();
	//measured in ms
	double elapsed_time = 1000 * ((double)(end-begin)/CLOCKS_PER_SEC);

	// output <<"Nearest neighbor: "<<pid<<std::endl;
	// output <<"distanceTrue: "<<db<<std::endl;
	// output <<"tTrue: "<<elapsed_time<<std::endl;
	cout <<"Nearest neighbor: "<<pid<<std::endl;
	cout <<"distanceTrue: "<<db<<std::endl;
	cout <<"tTrue: "<<elapsed_time<<std::endl;
	TrueDist = db;
}