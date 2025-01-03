#include <iostream>
#include <string>
#include "util.h"
#include "../libs/pugixml-1.14/src/pugixml.hpp"

std::map<std::string, std::string> parseRoutesFromXML(std::string filename){
    std::map<std::string, std::string> map_vehicles_routes;
    
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(filename.c_str());

    if (!result){
        std::cout << "Error: " << result.description() << std::endl;
        return map_vehicles_routes;
    }

    return map_vehicles_routes;
}