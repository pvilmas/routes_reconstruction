#include <cassert>
#include <iostream>
#include "../src/util.h"
#include "./utilTest.h"

void TestBinarySearch() {
    // Test 1: binary search should find an element that exists in the array
    int v[10] = {7, 10, 11, 22, 25, 30, 33, 40, 45, 50};
    int index = binarySearch(v, 10, 45);
    assert(("Element 45 should be found at index 8", index == 8));

    // Test 2: binary search should not find an element that does not exist in the array
    index = binarySearch(v, 10, 100);
    assert(("Element 100 shouldn't be found", index == -1));
}

int main() {

    TestBinarySearch();

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}