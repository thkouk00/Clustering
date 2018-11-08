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
#include "../include/Buckets.h"
#include "../include/normal_distr.h"

class HashTable
{
	int num_of_buckets;
	Buckets **buckets;
public:
	HashTable()
	{
		this->num_of_buckets = 0;
		this->buckets = NULL;
	};
	HashTable(int);
	~HashTable();
	void setVals(int);
	void insertPoint(int, std::string,std::vector<double>&, std::vector<int>);
	void printBucket(int);
	int get_num_of_buckets();
	bool bucket_exist(int);
	void printAll();
	Buckets* access_bucket(int&);
	void hashDataset(std::vector<std::vector<double>>&, std::vector<std::string> &, std::map<int,bool>&,int, int);
	//overloading function
	void hashDataset(std::vector<std::vector<double>>&, std::vector<std::string> &,int);

};




#endif