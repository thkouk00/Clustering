#include "../../include/Hypercube/cube_general_functions.h"

using namespace std;
extern bool metric;

//stores Dataset and QuerySet
void cube_storeDataset(std::vector<std::vector<double>> &dataset, std::vector<std::string> &id,char *input_file,int &hashTable_lines, bool &euclidean_flag, double &Radius)
{
    std::string line;
    std::ifstream myfile(input_file);
    int count_lines = 0;
   
	while (std::getline(myfile, line))
	{
		string str;
		std::vector<double> tmpv;
		std::istringstream iss (line);

		int val;
		double num;
		iss >> str;
		if (count_lines == 0)
		{
			if ( !str.compare("Euclidean") || !str.compare("euclidean") )
			{
				euclidean_flag = 1;
				count_lines++;
				continue;
			}	
			else if ( !str.compare("Cosine") || !str.compare("cosine") )
			{
				euclidean_flag = 0;
				count_lines++;
				continue;
			}
			else if (!str.compare("Radius:") || !str.compare("radius:") )
			{
				iss >> Radius;
				cout <<"Radius "<<Radius<<std::endl;
				count_lines++;
				continue;
			}
			else
			{
				// default metric -> euclidean
				euclidean_flag = 1;
				count_lines++;
			}
		}
		id.push_back(str);
		
		//first element
		iss >> val;
		while (!iss.eof())
		{
			tmpv.push_back(val);	
			iss >> val;
		}
		dataset.push_back(tmpv);
		
		tmpv.erase(tmpv.begin(),tmpv.end());	
		++hashTable_lines;
	}
}

// void search_neighbors(HashTable *cube,std::vector<std::string> &id,std::vector<std::vector<double>> &queryset,std::map<int,bool> &mymap,int &M, int &probes,int &k,int &w, int &num_of_buckets, double &Radius,bool &Euclidean,std::ofstream &output)
void cube_search_neighbors(std::map<std::vector<double>, MapNode>& assigned_elements, HashTable *cube,std::vector<std::string> &id,std::vector<std::vector<double>> &queryset,std::map<int,bool>& coinmap,int &M, int &probes,int &k,int &w, int &num_of_buckets, bool &Euclidean)
{
	int position;
	double maxfraction = 0;
	double ApproxDist = 0;
	// double TrueDist = 0;
	double averageApproxtime = 0;
	std::vector<double> query;
	std::vector<int> g; 
	string id_query;  

	double min_dist = 9999999;
	int num_of_clusters = queryset.size();
	for (int i=0;i<num_of_clusters;i++)
	{
		for (int j=i+1;j<num_of_clusters;j++)
		{
			double dist = Euclidean_Distance(queryset[i], queryset[j]);
			if (min_dist > dist)
				min_dist = dist;
		}
	}
	//starting radius
	double Rad = min_dist/2;
	int cluster_pos = 0;
	double Radius;

	std::vector<string>::iterator id_iter;
	std::vector<std::vector<double>>::iterator it;	
	for (id_iter=id.begin(), it=queryset.begin();it!=queryset.end();it++, id_iter++)
    {
    	 
		query = *it; 
		cube_find_hashFunction(g, query, coinmap, k, w, num_of_buckets, position,Euclidean);
		int TmpPos = position;
		
		long double dist = 0;
		string id;

		// Range_search(cube,g,query,TmpPos,M,probes,k,Radius,Euclidean,output,TrueDist);
		// cube_Range_search(cube,g,query,TmpPos,M,probes,k,Radius,Euclidean,TrueDist);
		
		if (Rad != 0)
		{	
			Radius = Rad;
			bool Stop_flag = 1;
			while(1)
			{
				// Range_search(hashTables,g,query,fi,L,k,Radius,Euclidean,output,TrueDist);
				cube_Range_search(assigned_elements, cube, g, query, queryset, TmpPos, M, probes, k, Radius, Euclidean, Stop_flag, cluster_pos);
				
				if (!Stop_flag)
					break;
				Radius = Radius * 2;
				if (Radius >= (Rad*10))
					break;
			}
		}
		cluster_pos++;
		// if (Radius != 0)
		// {
		// 	TmpPos = position;
		// 	//ApproxNN_search
		// 	NN_search(cube,g,query,TmpPos,M,probes,k,Euclidean,output,ApproxDist,averageApproxtime);
		// 	if (ApproxDist != 9999999.0 && TrueDist != 9999999.0 && TrueDist != 0)
		// 	{
		// 		double tmpfraction = ApproxDist/TrueDist; 
		// 		if (tmpfraction > maxfraction)
		// 		{
		// 			// cout <<"ApproxDist "<<ApproxDist<<" TrueDist "<<TrueDist<<std::endl;
		// 			// cout <<"BEFORE FR: "<<maxfraction<<" AFTER FR: "<<tmpfraction<<std::endl;
		// 			maxfraction = tmpfraction;
		// 		}
		// 	}
		// }
		// TrueDist = 0;
		query.clear();
		g.clear();
	}
}

int cube_find_hashFunction(std::vector<int> &g, std::vector<double> &query, std::map<int,bool> &mymap, int &k, int &w, int &num_of_buckets, int &position, bool Euclidean)
{
	int h;
	double t;
	std::vector<double> v;
	std::vector<int> tmpv;
	
	for (int i=0;i<k;i++)
	{
		//rerun generator in case of overflow
		while (1)
		{	
			//vector v same size as current vector size for use in inner_product
			normal_distr_generator(v,query.size());

			double in_product = std::inner_product(v.begin(), v.end(), query.begin(), 0);
			
			// if (Euclidean)
			if (metric == 1)
			{
				//random pick of t in [0,w) , double
				t = ((double)rand() / (RAND_MAX + 1.0)) * w ;
				//compute h(p)
				h = ((in_product+t)/w);
				//no overflow
				if (!check_overflow(h))
				{	
					//empty vector to take new values
					v.clear();
				}
				else
				{
					int bin;
					std::uniform_real_distribution<> dist(0, 1);
					std::map<int,bool>::iterator it;
					it = mymap.find(h);
					// not found
					if (it == mymap.end())
					{
						bin = random(1);
						mymap[h] = bin;
					}
					else 
						bin = it->second;		// key found
					
					tmpv.push_back(bin);
					break;
				}
			}
			else
			{
				if (in_product >= 0)
					h = 1;
				else
					h = 0;
				break;
			}
		}
		g.push_back(h);
		//empty vector to take new values
		v.clear();
	}
	// if (Euclidean)
	if (metric == 1)
		position = binarytodecimal(tmpv);
	else
		position = binarytodecimal(g);
	
	return position;
}