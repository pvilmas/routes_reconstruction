#include <iostream>
#include <fstream>
using namespace std;



int main(int argc, char *argv[]){
    if(argc < 4){
        cout << "Use: ./route_reconstruction.out <output.json> <original.rou.xml> \"<partition1.rou.xml> ...\"" << endl;
        return 1;
    }
    return 0;
}