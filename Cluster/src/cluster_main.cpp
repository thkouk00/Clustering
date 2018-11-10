#include <iostream>
#include <vector>
#include <string>
#include "../include/Initialization.h"

using namespace std;

int main(int argc, char const *argv[])
{
	//diavasma arxeion
	int num_of_lines = 20;
	int k = 5;
	std::vector<int> Cluster_Table;
	Random_Initialization(k,num_of_lines,Cluster_Table);

	std::vector<int>::iterator it;
	for (it = Cluster_Table.begin();it!= Cluster_Table.end();it++)
		cout <<*it<<' ';
	cout <<std::endl;

	int counter = 1;
	std::vector<std::vector<double>> Points;
	for (int i=0;i<5;i++)
	{
		std::vector<double> v;
		for (int y=0;y<3;y++)
		{
			v.push_back(counter);
			cout <<"Counter "<<counter<<std::endl;
			counter++;
		}
		cout <<"V size "<<v.size()<<std::endl;
		Points.push_back(v);
		v.clear();
	}
	K_means_plusplus(k, num_of_lines, Cluster_Table, Points);

	return 0;
}