#include <map>
#include <string>
#include <vector>
#include <set>

// Define the type for a segment (partition ID and list of edges)
typedef std::pair<std::string, std::vector<std::string>> Segment;

typedef std::vector<std::pair<std::string, std::vector<std::map<std::string, std::string>>>> ReconstructedVehicleRoute;

/*
 * Parse vehicle routes from a .rou.xml file.
 * 
 * @param filename a std::string containing the path to the .rou.xml file.
 * @return a std::map<char*, char*> mapping vehicle IDs to their routes.
 */
std::map<std::string, std::string> parseRoutesFromXML(std::string filename);

/*
 * Align segments to partitions.
 * 
 * @param vehicle_id a std::string containing the vehicle ID.
 * @param original_edge_list a std::vector<std::string> containing the original edge list.
 * @param edge_to_partition a std::map<std::string, std::set<std::string>> mapping edges to partitions.
 * @return a std::vector<Segment> containing the aligned segments.
 */
std::vector<Segment> alignSegmentsToPartitions(std::string vehicle_id, std::vector<std::string> original_edge_list, std::map<std::string, std::set<std::string>> edge_to_partition);

/* Split a string into a vector of strings based on a delimiter. 
 * 
 * @param s a std::string containing the string to split.
 * @param delimiter a std::string containing the delimiter to split the string by.
 * @return a std::vector<std::string> containing the split strings.
 */
std::vector<std::string> split(std::string s, std::string delimiter);

/* Reconstruction of the vehicle routes based on the partitioned routes.
 * @param original_routes a std::map<std::string, std::string> containing the original routes.
 * @param partitioned_routes a std::map<int, std::map<std::string, std::string>> containing the partitioned routes.
 * @return a std::pair<std::string, std::vector<std::map<std::string, std::string>>> containing the reconstructed vehicle routes.
 */
ReconstructedVehicleRoute reconstructRoutes(std::map<std::string, std::string> original_routes, std::map<int, std::map<std::string, std::string>> partitioned_routes);


/* Save data to a JSON file.
 * @param data a ReconstructedVehicleRoute containing the data to save.
 * @param filename a std::string containing the path to the JSON file.
 */
void saveToJson(ReconstructedVehicleRoute data, std::string filename);