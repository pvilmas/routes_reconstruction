#include <iostream>
#include <string>
#include "util.h"
#include "../libs/pugixml-1.14/src/pugixml.hpp"

std::map<std::string, std::string> parseRoutesFromXML(std::string filename){
    // create an empty map to store the vehicles and their routes
    std::map<std::string, std::string> map_vehicles_routes;
    
    // load the file
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(filename.c_str());

    // check if the file is empty
    if (result.status == pugi::status_no_document_element) {
        // if so return an empty map
        return map_vehicles_routes;
    // if there was another error loading the file
    } else if (!result) {
        // print the error and return an empty map
        std::cout << "Error: " << result.description() << std::endl;
        return map_vehicles_routes;
    }

    try {
        // first we get the root node
        pugi::xml_node root = doc.child("routes");
        // then we iterate over all the child nodes that are vehicles
        for (pugi::xml_node vehicle = root.child("vehicle"); vehicle; vehicle = vehicle.next_sibling("vehicle")) {
            // get the vehicle ID
            std::string vehicle_id = vehicle.attribute("id").value();
            // get the attr edges of the child route of each vehicle
            std::string vehicle_route = vehicle.child("route").attribute("edges").value();
            // store the vehicle ID and route in the map
            map_vehicles_routes[vehicle_id] = vehicle_route;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error parsing XML file " << filename << ": " << e.what() << std::endl;
    }

    return map_vehicles_routes;
}