OBJS=	Buckets.o HashTable.o Node.o normal_distr.o general_functions.o NN_search.o Range_search.o Distance.o main.o main_func.o
SOURCE=	./src/Buckets.cpp ./src/HashTable.cpp ./src/Node.cpp ./src/normal_distr.cpp ./src/general_functions.cpp ./src/NN_search.cpp ./src/Range_search.cpp ./src/Distance.cpp ./src/main.cpp ./src/main_func.cpp
HEADER=	./include/Buckets.h ./include/HashTable.h ./include/Node.h ./include/normal_distr.h ./include/general_functions.h ./include/NN_search.h ./include/Range_search.h ./include/Distance.h ./include/main_func.h
CC=	g++
FLAGS=	-c

all: $(OBJS)
	$(CC) -g3 -o lsh $(OBJS)

Buckets.o:	./src/Buckets.cpp
	$(CC) $(FLAGS) ./src/Buckets.cpp

HashTable.o:	./src/HashTable.cpp
	$(CC) $(FLAGS) ./src/HashTable.cpp

Node.o:	./src/Node.cpp
	$(CC) $(FLAGS) ./src/Node.cpp

normal_distr.o:	./src/normal_distr.cpp
	$(CC) $(FLAGS) ./src/normal_distr.cpp

general_functions.o:	./src/general_functions.cpp
	$(CC) $(FLAGS) ./src/general_functions.cpp

NN_search.o:	./src/NN_search.cpp
	$(CC) $(FLAGS) ./src/NN_search.cpp

Range_search.o:	./src/Range_search.cpp
	$(CC) $(FLAGS) ./src/Range_search.cpp

Distance.o:	./src/Distance.cpp
	$(CC) $(FLAGS) ./src/Distance.cpp

main.o:	./src/main.cpp
	$(CC) $(FLAGS) ./src/main.cpp

main_func.o:	./src/main_func.cpp
	$(CC) $(FLAGS) ./src/main_func.cpp


clean:	
	rm -rf lsh output* *.o
