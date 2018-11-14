all: cluster
LSH = ./src/LSH
Cluster = ./src/cluster


cluster:
	g++ -c $(Cluster)/Cluster.cpp $(Cluster)/cluster_main.cpp $(Cluster)/cluster_main_func.cpp $(Cluster)/Initialization.cpp $(Cluster)/Assignment.cpp $(Cluster)/Update.cpp $(Cluster)/Point_Info.cpp \
	$(LSH)/Buckets.cpp $(LSH)/HashTable.cpp $(LSH)/Node.cpp $(LSH)/normal_distr.cpp $(LSH)/general_functions.cpp $(LSH)/NN_search.cpp $(LSH)/Range_search.cpp $(LSH)/Distance.cpp $(LSH)/main_func.cpp
	g++ -o cluster *.o	

clean:
	rm -rf *.o cluster