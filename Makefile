CC = g++

# compile command to compile route_reconstruction.cpp
compile: src/routeReconstruction.cpp src/util.cpp
	$(CC) -o src/routeReconstruction.out src/routeReconstruction.cpp src/util.cpp

# execute the program
run: src/route_reconstruction.out
	./src/route_reconstruction.out routes/output.json routes/villadecans.rou.xml "routes/partition_0.rou.xml routes/partition_1.rou.xml routes/partition_2.rou.xml routes/partition_3.rou.xml routes/partition_4.rou.xml"

# compile tests
test: test/utilTest.cpp src/util.cpp
	$(CC) -o test/utilTest.out test/utilTest.cpp src/util.cpp

# run tests
test_run: test/utilTest.out
	./test/utilTest.out
