#include "util.h"

int binarySearch(int *v, int n, int x){
    int l = 0, r = n - 1;
    while(l <= r){
        int m = (l + r) / 2;
        if(v[m] == x) return m;
        if(v[m] < x) l = m + 1;
        else r = m - 1;
    }
    return -1;
}

std::map<char*, char*> parse_routes_from_xml(char* filename){
    std::map<char*, char*> map_vehicles_routes;
    
    
}