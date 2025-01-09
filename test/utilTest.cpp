#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "../src/util.h"
#include "./utilTest.h"

void TestSplit() {
    // Test 1: split should return a vector with one element when the delimiter is not found
    std::vector<std::string> tokens = split("test", ",");
    assert(("A string without the delimiter should return a vector with one element", tokens.size() == 1));

    // Test 2: split should return a vector with the correct number of elements
    tokens = split("test,test,test", ",");
    assert(("A string with the delimiter should return a vector with the correct number of elements", tokens.size() == 3));

    // Test 3: split should return a vector with the correct elements
    assert(("A string with the delimiter should return a vector with the correct elements", tokens[0] == "test" && tokens[1] == "test" && tokens[2] == "test"));
}

void TestParseRoutesFromXML() {
    // Test 1: parseRoutesFromXML should return an empty map when the file is empty
    std::map<std::string, std::string> map_vehicles_routes = parseRoutesFromXML("test/test_routes/empty.rou.xml");
    assert(("An empty XML returns an empty map", map_vehicles_routes.empty()));

    // Test 2: parseRoutesFromXML should return a map with the correct number of vehicles
    map_vehicles_routes = parseRoutesFromXML("test/test_routes/test_route.rou.xml");
    assert(("The map should have the correct number of vehicles", map_vehicles_routes.size() == 7));

    std::map<std::string, std::string> expected_map_vehicles_routes = {
    {"1", "102825242#1 97681571#4 97681571#5 102694207#0 102694207#1 102694207#2 102694207#3 95593743#2 95593743#3 665467170#0 665467170#1 665467170#2 665467170#3 665467170#4 665467170#5 665467170#6 665467170#7 665467170#8 665467170#9 96614440#1 539700223 539672015#0 98855834#0 98855834#1 98855834#2 98855834#3 98855834#4 98550013 437995546 98640750#0 98640750#1 98640750#2 -98989098#6 -98989098#5 -98989098#4 -98989098#3 -98989098#2"},
    {"2", "58801797#0 58801797#1 58801797#2 103964838#3 103964838#4 103964838#5 103964838#6 103964838#7 103964838#0 103964838#1 110058643#0 110058643#1 110058643#2 1104609142#1 1104609142#2 58801803#0 58801803#1 295047601#2 539861452#0 539861452#1 539667095#0 539667095#1 539667095#2 1165469152#0 1165469152#1 1165469152#2 1165469152#3 1165469154#5 1165469153#0 1165469153#1 1165469153#2 1165469153#3 1116009378#4 1116009378#0 1116009379#0 1116009379#1 1116009379#2 1116009379#3 1116009376#5 1116009376#0 1165469159#0 1165469159#1 1165469160 1116009377#0 1116009377#1 1116009377#2 1116009377#3 1116009377#4 97106112#3 97106119#0 97106119#1 97106119#2 97106119#3 97106119#4 97106119#5 208418744 208418743#0 208418743#1 96616031#2 909783275#0 909783275#1 909783275#2 909783275#3 96617608#0 438132552#1 438132546#1"},
    {"3", "96617277#1 96617277#2 96614421#1 96616040#0 96616040#1 539700922#0 96617272#0 96617272#1 96617273 -204331653#4 96617275#0 97680600#0 97680600#1 97678824#0 97678824#1 97678824#2 97678824#3 97678824#4 97678824#5 97678824#6 97678824#7 -97675054#8 -97675054#7 97772830#2 97772830#3 97772828#1 1029856084#3 539700920#0 539700920#1 539700920#2 539700920#3 20026755 540513236 -540714693#3 -540714693#2 -540714693#1 -540714693#0 540714692#0 540714692#1 540714692#2 -154766475#2 -154766475#1 -154766475#0 540512678 154766483#0 154766483#1 1018466676 154766476#0 154766476#1 154766476#2 540714689 154766496#0 154766496#1 154766496#2 564116377 383315646#0 383315646#1 383315646#2 383315646#3 383315646#4 540714687 540714686 540512681 564116378#0 564116378#1 437519467#0 437519467#1 437519467#2 437519467#3 437519467#4 437519467#5 -154766478#2 -154766478#1 -154766478#0"},
    {"6", "-1115991586#1 -1115991586#0 -1228972046 -1228972039 -1115991584#4 -1115991584#3 -1115991584#2 -1115991584#1 -1115991584#0 -1116322036#1 -1116322036#0 102825237#0 102825237#1 102825237#2 102825237#3 102825237#4 102825237#5 102825238 102694900#2 102694900#3 97535993#0 97535993#1 97535993#2 438147567 94137804#2 569027931 567558163#0 94137785 94137783 96346738#1 96346738#2 -94120358#6 -94120358#5"},
    {"7", "415698700 22875666#3 22875666#4 22875667 22875654#2 22875654#3 22875659#0 22875659#1 22875661#0 22875661#1 22875666#0 22875666#1 22875666#2"},
    {"9", "93951869#3 93950926#8 93976560#3 93950928#0 93950928#1 93950928#2 93950928#3 539672010#0 539672010#1 -101969263#1 -101969263#0 539672008 93917262 559486118#0 559486118#1 93917261#0 93917261#1 93917261#2 101962746#0 101962746#1 101962747#0 101962747#1 101962747#2 147855374#4 147855374#5 101966231 101966229#3 101966229#0 -101966235#7"},
    {"10", "93950935#0 539700229#0 539700229#1 93950520#0 93950928#3 539672010#0 539672010#1 -101969263#1 -101969263#0 539672008 539699080 93628276#0 94130235#0 94130235#1 94252661#0 94252661#1 -428130456#1 -428130456#0 567558163#0 567558163#1 438147565 -94137765 94137777 567558162 569027934 1232198391 95260872#0 95260872#1 93516579#4 93516579#0 -454549845 -232119712 -445900688#1 -445900688#0 -22700029 22699980#3 22699980#0 -188839136#1 -188839136#0 -188839137 188839135 -461396941 461396939#0 461396939#1"}
    };

    // Test 3: parseRoutesFromXML should return a map with the correct routes for each vehicle
    for (auto const& vehicle_route : expected_map_vehicles_routes) {
        std::string vehicle_id = vehicle_route.first;
        std::string expected_route = vehicle_route.second;
        assert(("The map should have the correct routes for each vehicle", map_vehicles_routes[vehicle_id] == expected_route));
    }
}

void TestAlignSegmentsToPartitions() {
    std::map<std::string, std::string> one_vehicle = parseRoutesFromXML("test/test_routes/one_vehicle_test.rou.xml");
    std::map<int, std::map<std::string, std::string>> partitioned_routes;  
    std::vector<std::string> partition_files = {
        "routes/partition_0.rou.xml",
        "routes/partition_1.rou.xml",
        "routes/partition_2.rou.xml",
        "routes/partition_3.rou.xml",
        "routes/partition_4.rou.xml",
    };

    //iterate over partition_files
    for (int i = 0; i < partition_files.size(); i++) {
        partitioned_routes[i] = parseRoutesFromXML(partition_files[i]);
    }

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

    std::vector<Segment> aligned_segments = alignSegmentsToPartitions("3", split(one_vehicle["3"], " "), edge_to_partition);

    // Expected segments
    std::pair<std::string, std::vector<std::string>> partition_0;
    partition_0.first = "0";
    partition_0.second = {"96617277#1", "96617277#2", "96614421#1", "96616040#0", "96616040#1", "539700922#0", "96617272#0", "96617272#1", "96617273", "-204331653#4", "96617275#0", "97680600#0", "97680600#1", "97678824#0", "97678824#1", "97678824#2", "97678824#3", "97678824#4", "97678824#5", "97678824#6", "97678824#7", "-97675054#8", "-97675054#7", "97772830#2", "97772830#3", "97772828#1", "1029856084#3", "539700920#0", "539700920#1", "539700920#2", "539700920#3", "20026755", "540513236", "-540714693#3", "-540714693#2", "-540714693#1", "-540714693#0", "540714692#0", "540714692#1", "540714692#2"};
    std::pair<std::string, std::vector<std::string>> partition_2;
    partition_2.first = "2";
    partition_2.second = {"-154766475#1", "-154766475#0", "540512678", "154766483#0", "154766483#1", "1018466676", "154766476#0", "154766476#1", "154766476#2", "540714689", "154766496#0", "154766496#1", "154766496#2", "564116377", "383315646#0", "383315646#1", "383315646#2", "383315646#3", "383315646#4", "540714687", "540714686", "540512681", "564116378#0", "564116378#1", "437519467#0", "437519467#1", "437519467#2", "437519467#3", "437519467#4", "437519467#5", "-154766478#2", "-154766478#1", "-154766478#0"};

    std::vector<Segment> expected_aligned_segments = {partition_0, partition_2};

    // Test 1: alignSegmentsToPartitions should return a vector with the correct number of segments
    assert(("The function should return a vector with the correct number of segments", aligned_segments.size() == expected_aligned_segments.size()));

    // Test 2: alignSegmentsToPartitions should return a vector with the correct segments
    for (int i = 0; i < aligned_segments.size(); i++) {
        assert(("The function should return a vector with the correct segments", aligned_segments[i].first == expected_aligned_segments[i].first && aligned_segments[i].second == expected_aligned_segments[i].second));
    }
}

int main() {

    TestSplit();
    TestParseRoutesFromXML();
    TestAlignSegmentsToPartitions();

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}