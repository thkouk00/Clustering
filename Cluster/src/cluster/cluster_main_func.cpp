#include "../../include/cluster/cluster_main_func.h"

using namespace std;

std::vector<std::vector<double>> Distance_Table;
std::vector<int> Cluster_position;
std::vector<int> tmp_Cluster_position;
bool metric;

void cluster_main_func(std::vector<std::vector<double>>& Points, std::vector<std::string>& id, std::string output_file, int& k, int& k_lsh, int& k_cube, int& L, int& w, int& M, int& probes, bool& metric_flag)
{
	metric = metric_flag;
	//write output to file
	std::ofstream outputfile;
	outputfile.open (output_file, ios::out | ios::trunc);

	std::vector<std::vector<double>> Cluster_Table;
	std::vector<std::vector<double>> tmp_Cluster_Table;
	
	// array to hold values 
	for (int i=0;i<Points.size();i++)
	{
		std::vector<double> v;
		Distance_Table.push_back(v);
		for (int j=i;j<Points.size();j++)
			Distance_Table[i].push_back(0);
	}	

	Cluster** cluster = new Cluster*[k];
	for (int i=0;i<k;i++)
		cluster[i] = new Cluster;

	//construct LSH or Hypercube structure only once 
	bool LSH_flag;
	// bool cube_flag = 0;
	HashTable *cube;
	HashTable **hashTables;
	
	int number_of_buckets;
	if (metric == 1)
		number_of_buckets = Points.size()/4;
	else
		number_of_buckets = pow(2,k_lsh);
	
	hashTables = new HashTable*[L];
	for (int i=0;i<L;i++)
	{
		hashTables[i] = new HashTable(number_of_buckets);
		if (metric == 1)
			hashTables[i]->hashDataset(Points,id,k_lsh,w);
		else
			hashTables[i]->hashDataset(Points,id,k_lsh);
	}

	// Hypercube Structure
	std::map<int,bool> coinmap;
	if (k_cube == -1)
		k_cube = (int)log2(Points.size());
	number_of_buckets = pow(2,k_cube); 
	cube = new HashTable(number_of_buckets);
	// Euclidean metric
	if (metric == 1)
		cube->hashDataset(Points, id, coinmap, k_cube, w);
	else
		cube->hashDataset(Points, id, k_cube);		//cosine metric

	//loop for initialization
	for (int q=0;q<2;q++)
	{			
		// initialization algorithms
		if (q == 0)
			Random_Initialization(tmp_Cluster_Table, Points, k);
		else
			K_means_plusplus(tmp_Cluster_Table, Points, k);


		bool k_means_flag;
		for (int r=0;r<6;r++)
		{
			Cluster_Table = tmp_Cluster_Table;
			Cluster_position = tmp_Cluster_position;
			outputfile <<"Algorithm: "<<q+1<<" x ";
			if (r == 0)
				outputfile <<1<<" x "<<1<<std::endl;
			else if (r == 1)
				outputfile <<1<<" x "<<2<<std::endl;
			else if (r == 2)
				outputfile <<2<<" x "<<1<<std::endl;
			else if (r == 3)
				outputfile <<2<<" x "<<2<<std::endl;
			else if (r == 4)
				outputfile <<3<<" x "<<1<<std::endl;
			else if (r == 5)
				outputfile <<3<<" x "<<2<<std::endl;
			
			if (metric_flag == 1)
				outputfile <<"Metric: Euclidean"<<std::endl;
			else
				outputfile <<"Metric: Cosine"<<std::endl;

			double old_objective = -1;
			int max_iter = 0;
			bool flag = 1;
			
			LSH_flag = 0;
			if ( r % 2 == 0)
				k_means_flag = 1;
			else
				k_means_flag = 0;
			
			std::map<std::vector<double>, std::vector<double>> new_map;
			std::map<std::vector<double>, std::vector<double>> old_map;
			
			auto start = chrono::high_resolution_clock::now();
			while (flag)
			{		
				double current_objective = 0;
				
				if (r == 0 || r == 1)
				{
					Lloyds_Assignment(new_map, cluster, Points, Cluster_Table, id, k_means_flag, current_objective);
				}
				else if (r == 2 || r == 3)
				{
					LSH_flag = 1;
					LSH_Assignment(new_map, hashTables, cluster, Points, Cluster_Table, id, k_lsh, L, w, k_means_flag);
				}
				else if (r == 4 || r == 5)
				{
					Hypercube_Assignment(new_map, cube, cluster, Points, Cluster_Table, id, coinmap, k_cube, M, probes, w, k_means_flag);
				}
				
				if (LSH_flag)
				{
					if (max_iter == 10)
					break;	
				}
				else
				{
					if (max_iter == 20)
						break;
				}
				
				
				if (k_means_flag)
				{
					//no change in assignments
					if (new_map == old_map)
						break;
					else
					{
						std::vector<std::vector<double>>::iterator pointIt;
						for (int n=0;n<Points.size();n++)
						{
							pointIt = find(Cluster_Table.begin(),Cluster_Table.end(),Points[n]);
							if (pointIt != Cluster_Table.end())
								continue;
						}
						old_map.clear();
						old_map = new_map;
						// new_map.clear();
					}
				}

				if (r % 2 == 0)
					k_means(cluster, Points, Cluster_Table, id);
				else
					PAM_improved(cluster, Points, Cluster_Table, id,flag);
				
				max_iter++;
				if (k_means_flag)
					new_map.clear();
			}

			auto end = chrono::high_resolution_clock::now();
			outputfile <<"clustering time: "<<chrono::duration_cast<chrono::seconds>(end-start).count()<<std::endl;

			for (int i=0;i<Cluster_Table.size();i++)
			{
				std::vector<Info> v = cluster[i]->get_array();
				if (!k_means_flag)
					outputfile <<"CLUSTER-"<<i+1<<" {size: "<<cluster[i]->get_array().size()<<", centroid: "<<id[Cluster_position[i]]<<"}"<<std::endl;
				else
				{
					outputfile <<"CLUSTER-"<<i+1<<" {size: "<<cluster[i]->get_array().size()<<", centroid: ";
					for (int j=0;j<Cluster_Table[i].size();j++)
					{
						if (j == Cluster_Table[i].size()-1)
							outputfile <<Cluster_Table[i][j]<<"}"<<std::endl;
						else	
							outputfile <<Cluster_Table[i][j]<<", ";
					}

				}
			}
			
			outputfile <<"Silhouette: ";
			double silhouette = Silhouette(Cluster_Table, cluster, k, k_means_flag, outputfile);
			outputfile <<std::endl;
		}
		Cluster_Table.clear();
		tmp_Cluster_Table.clear();
		Cluster_position.clear();
		tmp_Cluster_position.clear();

	}
	cout <<"END CLUSTERING"<<std::endl;	
	

	//close files
	outputfile.close();
	//free memory
	for (int i=0;i<k;i++)
		delete cluster[i];
	delete[] cluster;
	
	for (int i=0;i<L;i++)
		delete hashTables[i];
	delete[] hashTables;
	
	delete cube;
}