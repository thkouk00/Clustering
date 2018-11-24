#include "../../include/Hypercube/cube_HashTable.h"

using namespace std;

cube_HashTable::cube_HashTable(int num): num_of_buckets(num)
{
	this->buckets = new Buckets*[this->num_of_buckets];
	for (int i=0;i<this->num_of_buckets;i++)
		this->buckets[i] = NULL;
}

cube_HashTable::~cube_HashTable()
{
	for (int i=0;i<this->num_of_buckets;i++)
	{
		if (this->buckets[i])
			delete this->buckets[i];
	}
	delete[] this->buckets;
}

void cube_HashTable::cube_setVals(int num)
{
	this->num_of_buckets = num;
	for (int i=0;i<num_of_buckets;i++)
		this->buckets[i] = NULL;
}

void cube_HashTable::cube_insertPoint(int bucket_num,string id,vector<double> &v,std::vector<int> g)
{
	if (!this->buckets[bucket_num])
		this->buckets[bucket_num] = new Buckets(id,v,g);
	else
		this->buckets[bucket_num]->insertPointAtList(id,v,g);
}

void cube_HashTable::cube_printBucket(int bucket_num)
{
	if (this->buckets[bucket_num])
		this->buckets[bucket_num]->printList();
	else
		cout <<"Bucket not initialized"<<std::endl;
}

int cube_HashTable::cube_get_num_of_buckets()
{
	return this->num_of_buckets;
}

void cube_HashTable::cube_printAll()
{
	cout <<"#Buckets "<<this->num_of_buckets<<std::endl;
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
			int flag = this->cube_bucket_exist(i);
			cout <<"**FLAG IS "<<flag<<std::endl;
		}
	}
	cout <<"Total size is "<<counter<<std::endl;
}

bool cube_HashTable::cube_bucket_exist(int position)
{
	if (this->buckets[position] == NULL)
		return 0;
	else
		return 1;
}

Buckets* cube_HashTable::cube_access_bucket(int &position)
{
	if (this->buckets[position])
		return this->buckets[position];
	else
		return NULL;
}

// Euclidean Distance
void cube_HashTable::cube_hashDataset(std::vector<std::vector<double>> &dataset, std::vector<std::string> &id, std::map<int,bool> &mymap,int k,int w)
{
	int h;
	double t;
	std::vector<double> v;
	//holds all values from h
	std::vector<int> g;

	// use current time as seed for random generator
	std::srand(std::time(nullptr)); 

	vector<string>::iterator id_iter;
	vector< vector<double> >::iterator row;
	for(id_iter=id.begin(),row = dataset.begin(); row != dataset.end(); ++row,id_iter++)
	{
		std::vector<int> tmpv;
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
					v.erase(v.begin(),v.end());
				}
				else
					break;
			}
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
			{
				// key found
				bin = it->second;
			}
			g.push_back(h);
			tmpv.push_back(bin);
			//empty vector to take new values
			v.clear();
		}
		//convert binary number to decimal
		int pos = binarytodecimal(tmpv);
		//insert id and point to hashTable at pos bucket
		// optional -> hold g that has all the h that mapped to {0,1}
		this->cube_insertPoint(pos, *id_iter, *row,g);
		g.clear();
		tmpv.clear();
	}
}

// Cosine Similarity
void cube_HashTable::cube_hashDataset(std::vector<std::vector<double>> &dataset, std::vector<std::string> &id, int k)
{
	int h;
	int counter = 0;
	std::vector<int> g;
	std::vector<double> v;

	std::vector<string>::iterator id_iter;
	vector< vector<double> >::iterator row;
	for(id_iter=id.begin(), row = dataset.begin(); row != dataset.end(); ++row,++id_iter)
	{
		counter++;
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
		this->cube_insertPoint(position, *id_iter, *row,g);
		g.clear();
	}
}