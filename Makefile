CC = g++

# compile command to compile route_reconstruction.cpp
compile: src/routeReconstruction.cpp src/util.cpp libs/pugixml-1.14/src/pugixml.cpp
	$(CC) -o src/routeReconstruction.out src/routeReconstruction.cpp src/util.cpp libs/pugixml-1.14/src/pugixml.cpp

# execute the program
run: src/routeReconstruction.out
	./src/routeReconstruction.out routes/output_cpp.json routes/viladecans.rou.xml "routes/partition_0.rou.xml routes/partition_1.rou.xml routes/partition_2.rou.xml routes/partition_3.rou.xml routes/partition_4.rou.xml"

# execute python program
run_py:
	python3.9 src/route_reconstruction.py routes/output_py.json routes/viladecans.rou.xml [routes/partition_0.rou.xml routes/partition_1.rou.xml routes/partition_2.rou.xml routes/partition_3.rou.xml routes/partition_4.rou.xml]

# compile tests
test: test/utilTest.cpp src/util.cpp libs/pugixml-1.14/src/pugixml.cpp
	$(CC) -o test/utilTest.out test/utilTest.cpp src/util.cpp libs/pugixml-1.14/src/pugixml.cpp

# run tests
test_run: test/utilTest.out
	./test/utilTest.out

