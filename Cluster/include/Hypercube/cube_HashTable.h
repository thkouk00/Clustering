#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <numeric>
#include <bits/stdc++.h>
#include "../LSH/Buckets.h"
#include "../LSH/normal_distr.h"

class cube_HashTable
{
	int num_of_buckets;
	Buckets **buckets;
public:
	cube_HashTable()
	{
		this->num_of_buckets = 0;
		this->buckets = NULL;
	};
	cube_HashTable(int);
	~cube_HashTable();
	void cube_setVals(int);
	void cube_insertPoint(int, std::string,std::vector<double>&, std::vector<int>);
	void cube_printBucket(int);
	int cube_get_num_of_buckets();
	bool cube_bucket_exist(int);
	void cube_printAll();
	Buckets* cube_access_bucket(int&);
	void cube_hashDataset(std::vector<std::vector<double>>&, std::vector<std::string> &, std::map<int,bool>&,int, int);
	//overloading function
	void cube_hashDataset(std::vector<std::vector<double>>&, std::vector<std::string> &,int);

};




#endif