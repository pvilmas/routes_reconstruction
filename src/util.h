#include <map>

/*
 * Parse vehicle routes from a .rou.xml file.
 * 
 * @param filename the path to the .rou.xml file.
 * @return a std::map<char*, char*> mapping vehicle IDs to their routes.
 */
std::map<char*, char*> parseRoutesFromXML(char* filename);
