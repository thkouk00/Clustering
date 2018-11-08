OBJS =	Initialization.o 
SOURCE =	./src/Initialization.cpp
HEADER =	./include/Initialization.h
CC =	g++
FLAGS =	-c

all:	$(OBJS)
	$(CC) -g3 -o cluster $(OBJS)

Initialization.o:	./src/Initialization.cpp
	$(CC) $(FLAGS) ./src/Initialization.cpp


clean:	
	rm -rf cluster output* *.o