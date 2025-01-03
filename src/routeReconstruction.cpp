#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "util.h"

int main(int argc, char *argv[]){
    if(argc < 4){
        std::cout << "Use: ./src/route_reconstruction.out <./routes/output.json> <./routes/original.rou.xml> \"<./routes/partition1.rou.xml> ...\"" << std::endl;
        return 1;
    }

    // store paths in variables
    std::string output_path = argv[1];
    std::string original_path = argv[2];
    char* partition_paths = argv[3];

    // split partition paths by space and store them in an array of strings
    char* partition_path = strtok(partition_paths, " ");
    std::string str(partition_path);

    // assing routes to vehicles from xml
    std::map<std::string, std::string> map_vehicles_routes = parseRoutesFromXML(original_path);

    return 0;
}