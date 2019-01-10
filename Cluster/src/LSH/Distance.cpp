#include "../../include/LSH/Distance.h"

extern std::vector<std::vector<double>> Distance_Table;
extern std::vector<int> Cluster_position;
extern bool metric;

long double Euclidean_Distance(std::vector<double> & A, std::vector<double> &B)
{
 	long double sum = 0;
 	for(unsigned int i = 0;i<A.size();i++)
 	{
 		sum += pow((double)(A[i] - B[i]),2);
 	}
 	
 	return sqrtl(sum);
};

long double Cosine_Similarity(std::vector<double> &A, std::vector<double> &B)
{
	long double in_product = 0.0;
	double d_a = 0.0;
	double d_b = 0.0 ;

	if (A.size() != B.size())
	{
		std::cout <<"Asize "<<A.size()<<" Bsize "<<B.size()<<std::endl;
		throw std::logic_error("Vector A and Vector B are not the same size");
	}

    // Prevent Division by zero
	if (A.size() < 1)
	{
		std::cerr <<"Vector A and Vector B are empty"<<std::endl;
		//throw std::logic_error("Vector A and Vector B are empty");
	}

	in_product = std::inner_product(A.begin(), A.end(), B.begin(), 0.0);
	for(std::vector<double>::iterator A_iter = A.begin(), B_iter=B.begin(); A_iter != A.end(); A_iter++ , B_iter++ )
	{
		// mul += *A_iter * *B_iter;
		d_a += *A_iter * *A_iter;
		d_b += *B_iter * *B_iter;
	}

	if (d_a == 0.0f || d_b == 0.0f)
	{
		std::cerr <<"cosine similarity is not defined whenever one or both input vectors are zero-vectors.";
	}

	return in_product / (sqrt(d_a) * sqrt(d_b));
}

double Find_Distance(std::vector<double>& A, std::vector<double>& B, int& posA, int& posB)
{
	int min;
	int max;
	int position;
	if (posA > posB)
	{
		min = posB;
		max = posA;
	}
	else
	{
		min = posA;
		max = posB;	
	}

	double distance;
	position = max - min;
	
	if (Distance_Table[min][position] != 0)
	{
		distance = Distance_Table[min][position]; 
	}
	else
	{
		if (metric == 1)
			distance = Euclidean_Distance(A, B);
		else
			distance = 1 - Cosine_Similarity(A, B);

		Distance_Table[min][position] = distance;
	}

	return distance;
}