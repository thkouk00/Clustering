LSH = ./src/LSH
LSHH = ./include/LSH
Cluster = ./src/cluster
ClusterH = ./include/cluster
OBJS1 = Buckets.o HashTable.o Node.o normal_distr.o general_functions.o NN_search.o Range_search.o Distance.o main_func.o
SOURCE1 = $(LSH)/Buckets.cpp $(LSH)/HashTable.cpp $(LSH)/Node.cpp $(LSH)/normal_distr.cpp $(LSH)/general_functions.cpp $(LSH)/NN_search.cpp $(LSH)/Range_search.cpp $(LSH)/Distance.cpp $(LSH)/main_func.cpp
HEADER1 =  $(LSHH)/Buckets.h $(LSHH)/HashTable.h $(LSHH)/Node.h $(LSHH)/normal_distr.h $(LSHH)/general_functions.h $(LSHH)/NN_search.h $(LSHH)/Range_search.h $(LSHH)/Distance.h $(LSHH)/main_func.h
OBJS2 = Cluster.o cluster_main.o cluster_main_func.o Initialization.o Assignment.o Update.o Point_Info.o
SOURCE2 = $(Cluster)/Cluster.cpp $(Cluster)/cluster_main.cpp $(Cluster)/cluster_main_func.cpp $(Cluster)/Initialization.cpp $(Cluster)/Assignment.cpp $(Cluster)/Update.cpp $(Cluster)/Point_Info.cpp
HEADER2 =  $(ClusterH)/Cluster.h $(ClusterH)/cluster_main.h $(ClusterH)/cluster_main_func.h $(ClusterH)/Initialization.h $(ClusterH)/Assignment.h $(ClusterH)/Update.h $(ClusterH)/Point_Info.h

all: $(OBJS1) $(OBJS2) 
	g++ -o cluster $(OBJS1) $(OBJS2)

Buckets.o:	$(LSH)/Buckets.cpp
	g++ -c $(LSH)/Buckets.cpp

HashTable.o:	$(LSH)/HashTable.cpp
	g++ -c $(LSH)/HashTable.cpp

Node.o:	$(LSH)/Node.cpp
	g++ -c $(LSH)/Node.cpp

normal_distr.o:	$(LSH)/normal_distr.cpp
	g++ -c $(LSH)/normal_distr.cpp

general_functions.o:	$(LSH)/general_functions.cpp
	g++ -c $(LSH)/general_functions.cpp

NN_search.o:	$(LSH)/NN_search.cpp
	g++ -c $(LSH)/NN_search.cpp

Range_search.o:	$(LSH)/Range_search.cpp
	g++ -c $(LSH)/Range_search.cpp

Distance.o:	$(LSH)/Distance.cpp
	g++ -c  $(LSH)/Distance.cpp

main_func.o:	$(LSH)/main_func.cpp
	g++ -c $(LSH)/main_func.cpp

Cluster.o:	$(Cluster)/Cluster.cpp
	g++ -c $(Cluster)/Cluster.cpp

cluster_main.o:	$(Cluster)/cluster_main.cpp
	g++ -c $(Cluster)/cluster_main.cpp

cluster_main_func.o:	$(Cluster)/cluster_main_func.cpp
	g++ -c $(Cluster)/cluster_main_func.cpp

Initialization.o:	$(Cluster)/Initialization.cpp
	g++ -c $(Cluster)/Initialization.cpp

Assignment.o:	$(Cluster)/Assignment.cpp
	g++ -c $(Cluster)/Assignment.cpp

Update.o:	$(Cluster)/Update.cpp
	g++ -c $(Cluster)/Update.cpp

Point_Info.o:	$(Cluster)/Point_Info.cpp
	g++ -c $(Cluster)/Point_Info.cpp

clean:
	rm -rf *.o cluster