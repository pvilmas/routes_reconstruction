#include <iostream>
#include <fstream>
#include "util.h"

int main(int argc, char *argv[]){
    if(argc < 4){
        std::cout << "Use: ./route_reconstruction.out <output.json> <original.rou.xml> \"<partition1.rou.xml> ...\"" << std::endl;
        return 1;
    }

    int v[10] = {7, 10, 11, 22, 25, 30, 33, 40, 45, 50};

    int index = binary_search(v, 10, 45);

    if(index != -1) std::cout << "Element found at index " << index << std::endl;
    else std::cout << "Element not found" << std::endl;

    return 0;
}