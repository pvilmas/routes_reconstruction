#include <map>
#include <string>

/*
 * Parse vehicle routes from a .rou.xml file.
 * 
 * @param filename the path to the .rou.xml file.
 * @return a std::map<char*, char*> mapping vehicle IDs to their routes.
 */
std::map<std::string, std::string> parseRoutesFromXML(std::string filename);
