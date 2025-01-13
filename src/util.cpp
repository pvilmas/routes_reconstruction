#include <iostream>
#include <string>
#include "util.h"
#include "../libs/pugixml-1.14/src/pugixml.hpp"

std::vector<std::string> split(std::string s, std::string delimiter) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);

    return tokens;
}

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

std::vector<Segment> alignSegmentsToPartitions(std::string vehicle_id, std::vector<std::string> original_edge_list, std::map<std::string, std::set<std::string>> edge_to_partition) {
    
    std::vector<Segment> aligned_segments;
    std::string current_partition_id = "";
    std::vector<std::string> current_segment;

    for (std::string edge : original_edge_list) {
        std::set<std::string> partitions = edge_to_partition[edge];
        
        // if the edge does not belong to any partition
        // print a warning and skip the edge
        if (partitions.empty()) {
            std::cerr << "Warning: Edge " << edge << " for vehicle " << vehicle_id << " not found in any partition." << std::endl;
            continue;
        }

        // if there is no current partition, assign the first partition to the current partition
        if (current_partition_id == "") {
            current_partition_id = *partitions.begin();
        }

        // if the current partition is not in the set of partitions for the edge
        // add the current segment to the aligned segments and start a new segment
        if (partitions.find(current_partition_id) == partitions.end()) {
            aligned_segments.push_back(std::make_pair(current_partition_id, current_segment));
            current_partition_id = *partitions.begin();
            current_segment.clear();
        }

        // add the edge to the current segment
        current_segment.push_back(edge);
    }

    // add the last segment to the aligned segments
    if (!current_segment.empty()) {
        aligned_segments.push_back(std::make_pair(current_partition_id, current_segment));
    }

    return aligned_segments;
}

ReconstructedVehicleRoute reconstructRoutes(std::map<std::string, std::string> original_routes, std::map<int, std::map<std::string, std::string>> partitioned_routes) {
    std::map<std::string, std::set<std::string>> edge_to_partition;
    for (auto i : partitioned_routes) {
        int partition_id = i.first;
        std::map<std::string, std::string> vehicles = i.second;
        for (auto j : vehicles) {
            std::string vehicle_id = j.first;
            std::string edges = j.second;
            std::vector<std::string> list_edges = split(edges, " ");
            for (auto edge : list_edges) {
                // if edge not in edge_to_partition, add it with an empty set
                if (edge_to_partition.find(edge) == edge_to_partition.end()) {
                    edge_to_partition[edge] = std::set<std::string>();
                }
                // add the partition_id to the set of partitions for the edge
                edge_to_partition[edge].insert(std::to_string(partition_id));
            }
        }
    }

    ReconstructedVehicleRoute reconstructed_routes;

    // first iterate over the original routes map
    for (auto i : original_routes) {
        std::string vehicle_id = i.first;
        std::string original_edges = i.second;
        std::vector<std::string> original_edges_list = split(original_edges, " ");
        
        // align the segments to the partitions
        std::vector<Segment> segments = alignSegmentsToPartitions(vehicle_id, original_edges_list, edge_to_partition);

        // store the reconstructed route
        std::vector<std::map<std::string, std::string>> cut_routes;

        // iterate over the segments
        int j = 0;
        for (Segment segment : segments) {
            std::string next_partition = "-1";
            std::string next_route = "";
            
            // if the segment is not the last one
            if (j < segments.size() - 1) {
                next_partition = segments[j + 1].first;
                for (std::string edge : segments[j + 1].second) {
                    next_route += edge + " ";
                }
                // remove the last space
                next_route.pop_back();
            }

            std::string partition_id = segment.first;
            std::vector<std::string> edges = segment.second;
            std::string cut_route = "";
            for (std::string edge : edges) {
                cut_route += edge + " ";
            }
            //remove the last space
            cut_route.pop_back();

            // store the partition ID, vehicle ID, cut route, next partition, and next route
            std::map<std::string, std::string> partition_route = {
                {"partition", partition_id},
                {"id", vehicle_id},
                {"cut_route", cut_route},
                {"next_partition", next_partition},
                {"next_route", next_route}
            };

            // add the partition route to the cut routes
            cut_routes.push_back(partition_route);

            j++;
        }

        // store the reconstructed vehicle route
        reconstructed_routes.push_back(std::make_pair(original_edges, cut_routes));
    }

    return reconstructed_routes;
}