#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <chrono>
#include "util.h"

int main(int argc, char *argv[]){
    // register initial time
    auto start = std::chrono::high_resolution_clock::now();

    if(argc < 4){
        std::cout << "Use: ./src/route_reconstruction.out <./routes/output.json> <./routes/original.rou.xml> \"<./routes/partition1.rou.xml> ...\"" << std::endl;
        return 1;
    }

    // store paths in variables
    std::string output_file = argv[1];
    std::string osm_file = argv[2];
    std::string partition_files = argv[3];

    // split partition paths by space and store them in an array of strings
    std::vector<std::string> partition_files_vector = split(partition_files, " ");

    // assing routes to vehicles from xml
    std::map<std::string, std::string> original_routes = parseRoutesFromXML(osm_file);

    std::map<int, std::map<std::string, std::string>> partitioned_routes;
    // assign routes to partitions from xml
    for (int i = 0; i < partition_files_vector.size(); i++) {
        partitioned_routes[i] = parseRoutesFromXML(partition_files_vector[i]);
    }

    // reconstruct routes
    ReconstructedVehicleRoute reconstructed_routes = reconstructRoutes(original_routes, partitioned_routes);

    // save reconstructed routes to json
    saveToJson(reconstructed_routes, output_file);

    std::cout << "Reconstructed routes saved successfully to " << output_file << "." << std::endl;
    
    // register final time in a file
    auto end = std::chrono::high_resolution_clock::now();
    std::ofstream time_file;
    time_file.open("cpp_time.txt");
    // time in seconds with 2 decimal places
    time_file << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0 << " seconds";
    time_file.close();

    return 0;
}