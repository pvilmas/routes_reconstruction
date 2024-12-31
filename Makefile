CC = g++

# compile command to compile route_reconstruction.cpp
compile: route_reconstruction.cpp util.cpp
	$(CC) -o route_reconstruction.out route_reconstruction.cpp util.cpp

# execute the program
run: route_reconstruction.out
	./route_reconstruction.out output.json villadecans.rou.xml "partition_0.rou.xml partition_1.rou.xml partition_2.rou.xml partition_3.rou.xml partition_4.rou.xml"