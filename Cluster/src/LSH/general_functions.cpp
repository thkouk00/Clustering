#include "../../include/LSH/general_functions.h"

using namespace std;
extern bool metric;

//stores Dataset and QuerySet
void storeDataset(std::vector<std::vector<double>> &dataset, std::vector<std::string> &id,char *input_file,int &hashTable_lines, bool &euclidean_flag, double &Radius)
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
		line.clear();
	}
}

void search_neighbors(std::map<std::vector<double>, MapNode>& assigned_elements, HashTable **hashTables,std::vector<std::string> &id,std::vector<std::vector<double>> &queryset,int &L,int &k,int &w, int &num_of_buckets, bool Euclidean) 
{
	int counter=0;
	int tmpfi;
	// double maxfraction = 0;
	// double ApproxDist = 0;
	double TrueDist = 0;
	// double averageApproxtime = 0;
	std::vector<int> fi;
	std::vector<int> tmpg; 
	std::vector<double> query;
	std::vector<std::vector<int>> g;
	string id_query;  

	//calculate starting Radius
	//min dist between centers divided by 2
	double min_dist = 9999999;
	int num_of_clusters = queryset.size();
	for (int i=0;i<num_of_clusters-1;i++)
	{
		for (int j=i+1;j<num_of_clusters;j++)
		{
			double dist;
			if (metric == 1)
				dist = Euclidean_Distance(queryset[i], queryset[j]);
			else
				dist = 1 - Cosine_Similarity(queryset[i], queryset[j]);

			if (min_dist > dist)
				min_dist = dist;
		}
	}
	//starting radius
	double Rad = min_dist/2;
	// cout <<"initial rad "<<Rad<<std::endl;
	double Radius;
	int cluster_pos = 0;

	std::vector<string>::iterator id_iter;
    for (int i=0;i<queryset.size();i++)
    {
    	counter++;
    	 
    	// query = *it;
    	query = queryset[i];
		// create L*fi hashFunctions and L*g Functions for every query
		for (int i=0;i<L;i++)
		{
			find_hashFunction(tmpg, query, k, w, num_of_buckets, tmpfi,Euclidean);
			g.push_back(tmpg);
			fi.push_back(tmpfi);
			tmpg.erase(tmpg.begin(),tmpg.end());
		}
		
		long double dist = 0;
		string id;
		
		Radius = Rad;
		bool Stop_flag = 1;
		while(1)
		{
			// Range_search(assigned_elements,hashTables,g,query,queryset,fi,L,k,Radius,Euclidean,Stop_flag,cluster_pos);
			Range_search(assigned_elements,hashTables,g,query,queryset,fi,L,k,Radius,Euclidean,Stop_flag,i);
			if (!Stop_flag)
				break;
			Radius = Radius * 2;
			if (Radius >= (Rad*10))
				break;
		}
		cluster_pos++;

		// if (Radius != 0)
		// {
		// 	//ApproxNN_search
		// 	NN_search(hashTables,g,query,fi,L,k,Euclidean,output,ApproxDist,averageApproxtime);
		// 	if (ApproxDist != 9999999.0 && TrueDist != 9999999.0 && TrueDist != 0)
		// 	{
		// 		double tmpfraction = ApproxDist/TrueDist; 
		// 		if (tmpfraction > maxfraction)
		// 		{
		// 			maxfraction = tmpfraction;
		// 		}
		// 	}
			
		// }
		query.erase(query.begin(),query.end());
		g.erase(g.begin(),g.end());
		fi.erase(fi.begin(),fi.end());
	}
}


// void search_neighbors(HashTable **hashTables,std::vector<std::string> &id,std::vector<std::vector<double>> &queryset,int &L,int &k,int &w, int &num_of_buckets, double &Radius,bool Euclidean,std::ofstream &output)
void search_neighbors(HashTable **hashTables,std::vector<std::string> &id,std::vector<std::vector<double>> &queryset,int &L,int &k,int &w, int &num_of_buckets, double &Radius,bool Euclidean)
{
	int counter=0;
	int tmpfi;
	double maxfraction = 0;
	double ApproxDist = 0;
	double TrueDist = 0;
	double averageApproxtime = 0;
	std::vector<int> fi;
	std::vector<int> tmpg; 
	std::vector<double> query;
	std::vector<std::vector<int>> g;
	string id_query;  

	std::vector<string>::iterator id_iter;
	std::vector<std::vector<double>>::iterator it;	
	for (id_iter=id.begin(), it=queryset.begin();it!=queryset.end();it++, id_iter++)
    {
    	counter++;
    	 
    	query = *it;
		// create L*fi hashFunctions and L*g Functions for every query
		for (int i=0;i<L;i++)
		{
			find_hashFunction(tmpg, query, k, w, num_of_buckets, tmpfi,Euclidean);
			g.push_back(tmpg);
			fi.push_back(tmpfi);
			tmpg.erase(tmpg.begin(),tmpg.end());
		}

		// output <<std::endl<<"******************************************************************************************************************"<<std::endl;
		// output <<"Query: "<<*id_iter<<std::endl;
		cout <<std::endl<<"******************************************************************************************************************"<<std::endl;
		cout <<"Query: "<<*id_iter<<std::endl;
		
		long double dist = 0;
		string id;
		
		// Range_search(hashTables,g,query,fi,L,k,Radius,Euclidean,output,TrueDist);
		Range_search(hashTables,g,query,fi,L,k,Radius,Euclidean,TrueDist);
		
		// if (Radius != 0)
		// {
		// 	//ApproxNN_search
		// 	NN_search(hashTables,g,query,fi,L,k,Euclidean,output,ApproxDist,averageApproxtime);
		// 	if (ApproxDist != 9999999.0 && TrueDist != 9999999.0 && TrueDist != 0)
		// 	{
		// 		double tmpfraction = ApproxDist/TrueDist; 
		// 		if (tmpfraction > maxfraction)
		// 		{
		// 			maxfraction = tmpfraction;
		// 		}
		// 	}
			
		// }
		query.erase(query.begin(),query.end());
		g.erase(g.begin(),g.end());
		fi.erase(fi.begin(),fi.end());
	}
	// output <<std::endl<<"Final Statistics:"<<std::endl;
	// output <<"Max fraction: "<<maxfraction<<std::endl;
	// output <<"Average Time of ApproxSearch: "<<averageApproxtime/(queryset.size())<<std::endl;
	cout <<std::endl<<"Final Statistics:"<<std::endl;
	cout <<"Max fraction: "<<maxfraction<<std::endl;
	cout <<"Average Time of ApproxSearch: "<<averageApproxtime/(queryset.size())<<std::endl;
}

int find_hashFunction(std::vector<int> &g, std::vector<double> &query, int &k, int &w, int &num_of_buckets, int &fi, bool Euclidean)
{
	int counter=0;
	// int fi;
	int h;
	double t;
	std::vector<double> v;
	for (int i=0;i<k;i++)
	{
		//rerun generator in case of overflow
		while (1)
		{	
			//vector v same size as current vector size for use in inner_product
			normal_distr_generator(v,query.size());

			// double in_product = std::inner_product(row->begin(), row->end(), v.begin(), 0);
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
					break;
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
	{
		std::hash<std::string> hash_fn;
		string hashstr;
		for (std::vector<int>::iterator it=g.begin();it!=g.end();it++)
			hashstr += to_string(*it);

		fi = hash_fn(hashstr) % num_of_buckets;
	}
	else
		fi = binarytodecimal(g);
	
	return fi;
}