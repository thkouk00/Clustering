#include "../include/HashTable.h"

using namespace std;

HashTable::HashTable(int num): num_of_buckets(num)
{
	this->buckets = new Buckets*[this->num_of_buckets];
	for (int i=0;i<num_of_buckets;i++)
		this->buckets[i] = NULL;
}

HashTable::~HashTable()
{
	for (int i=0;i<this->num_of_buckets;i++)
	{
		if (this->buckets[i])
			delete this->buckets[i];
	}
	delete[] this->buckets;
}

void HashTable::setVals(int num)
{
	this->num_of_buckets = num;
	for (int i=0;i<num_of_buckets;i++)
		this->buckets[i] = NULL;
}

void HashTable::insertPoint(int bucket_num,string id,vector<double> &v,std::vector<int> g)
{
	if (!this->buckets[bucket_num])
		this->buckets[bucket_num] = new Buckets(id,v,g);
	else
		this->buckets[bucket_num]->insertPointAtList(id,v,g);
}

void HashTable::printBucket(int bucket_num)
{
	if (this->buckets[bucket_num])
		this->buckets[bucket_num]->printList();
	else
		cout <<"Bucket not initialized"<<std::endl;
}

int HashTable::get_num_of_buckets()
{
	return this->num_of_buckets;
}

void HashTable::printAll()
{
	int counter=0;		
	for (int i=0;i<this->num_of_buckets;i++)
	{
		if (this->buckets[i])
		{
			counter += this->buckets[i]->bucket_size();
			cout <<"Bucket "<<i<<" is Active"<<std::endl;
		}
		else
		{
			cout <<"Bucket "<<i<<" *NOT* Active"<<std::endl;
			int flag = this->bucket_exist(i);
			cout <<"**FLAG IS "<<flag<<std::endl;
		}
	}
	cout <<"Total size is "<<counter<<std::endl;
}

bool HashTable::bucket_exist(int position)
{
	if (this->buckets[position] == NULL)
		return 0;
	else
		return 1;
}

Buckets* HashTable::access_bucket(int &position)
{
	if (this->buckets[position])
		return this->buckets[position];
	else
		return NULL;
}

// Euclidean Distance
void HashTable::hashDataset(std::vector<std::vector<double>> &dataset, std::vector<std::string> &id,int k, int w)
{
	//must find position of bucket first
	int counter=0;
	int fi;
	int h;
	double t;
	std::vector<double> v;
	//holds all values from h
	std::vector<int> g;
	int M = (int)(pow(2, 32)) - 5;

	// use current time as seed for random generator
	std::srand(std::time(nullptr)); 

	vector<string>::iterator id_iter;
	vector< vector<double> >::iterator row;
	for(id_iter=id.begin(),row = dataset.begin(); row != dataset.end(); ++row,id_iter++)
	{
		//must do this k times and put results in g
		for (int i=0;i<k;i++)
		{	
			//rerun generator in case of overflow
			while (1)
			{	
				//vector v same size as current vector size for use in inner_product
				normal_distr_generator(v,row->size());
				//random pick of t in [0,w) , double
				t = ((double)rand() / (RAND_MAX + 1.0)) * w ;
				double in_product = std::inner_product(v.begin(), v.end(), row->begin(), 0);
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
			g.push_back(h);
			//empty vector to take new values
			v.clear();
		}

		//compute fi , num_of_buckets = tablesize/4
		std::hash<std::string> hash_fn;
		string hashstr;
		for (std::vector<int>::iterator g_iter=g.begin();g_iter!=g.end();g_iter++)
			hashstr += to_string(*g_iter);
		fi = hash_fn(hashstr) % num_of_buckets;

		//insert id and point to hashTable at fi bucket
		this->insertPoint(fi, *id_iter, *row,g);
		g.clear();
	}
}

// Cosine Similarity
void HashTable::hashDataset(std::vector<std::vector<double>> &dataset, std::vector<std::string> &id, int k)
{
	int h;
	std::vector<int> g;
	std::vector<double> v;

	std::vector<string>::iterator id_iter;
	vector< vector<double> >::iterator row;
	for(id_iter=id.begin(), row = dataset.begin(); row != dataset.end(); ++row,++id_iter)
	{
		for (int i=0;i<k;i++)
		{		
			//vector v same size as current vector size for use in inner_product
			normal_distr_generator(v,row->size());
			//random pick of t in [0,w) , double
			double in_product = std::inner_product(v.begin(), v.end(), row->begin(), 0);
			//compute h(p)
			if (in_product>=0)
				h = 1;
			else
				h = 0;

			g.push_back(h);
			//empty vector to take new values
			v.clear();
		}
		long int position = binarytodecimal(g);
		this->insertPoint(position, *id_iter, *row,g);
		g.clear();
	}
}