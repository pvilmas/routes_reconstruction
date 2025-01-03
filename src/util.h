#include <map>

/*
 * Function to search for an element in a sorted array using binary search.
 *
 * @param v: pointer to the array
 * @param n: size of the array
 * @param x: element to be searched
 * @return index of the element if found, -1 otherwise
 */
int binarySearch(int *v, int n, int x);

/*
 * Parse vehicle routes from a .rou.xml file.
 * 
 * @param filename the path to the .rou.xml file.
 * @return a std::map<char*, char*> mapping vehicle IDs to their routes.
 */
std::map<char*, char*> parse_routes_from_xml(char* filename);
