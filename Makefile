all:
	(cd ./LSH ; make)
	(cd ./Hypercube ; make)
	(cd ./Cluster ; make)

clean:	
	(cd ./LSH ; make clean)
	(cd ./Hypercube ; make clean)
	(cd ./Cluster ; make clean)