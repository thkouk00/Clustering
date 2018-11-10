OBJS =	Initialization.o cluster_main.o cluster_main_func.o Cluster.o Assignment.o Point_Info.o #main_func.o
SOURCE =	./src/Initialization.cpp ./src/cluster_main.cpp ./src/cluster_main_func.cpp ./src/Cluster.cpp ./src/Assignment.cpp ./src/Point_Info.cpp #./LSH/src/main_func.cpp
HEADER =	./include/Initialization.h ./include/cluster_main.h ./include/cluster_main_func.h ./include/Cluster.h ./include/Assignment.h ./include/Point_Info.h #./LSH/include/main_func.h
CC =	g++
FLAGS =	-c

all:	$(OBJS)
	(cd ./LSH ; make)
	$(CC) -g3 -o cluster $(OBJS) ./LSH/*.o

Initialization.o:	./src/Initialization.cpp
	$(CC) $(FLAGS) ./src/Initialization.cpp

# Distance.o:	./src/Distance.cpp
# 	$(CC) $(FLAGS) ./src/Distance.cpp

cluster_main.o:	./src/cluster_main.cpp
	$(CC) $(FLAGS) ./src/cluster_main.cpp

cluster_main_func.o:	./src/cluster_main_func.cpp
	$(CC) $(FLAGS) ./src/cluster_main_func.cpp		

Cluster.o:	./src/Cluster.cpp
	$(CC) $(FLAGS) ./src/Cluster.cpp

Assignment.o:	./src/Assignment.cpp
	$(CC) $(FLAGS) ./src/Assignment.cpp

Point_Info.o:	./src/Point_Info.cpp
	$(CC) $(FLAGS) ./src/Point_Info.cpp

clean:	
	(cd ./LSH ; make clean)
	rm -rf cluster output* *.o