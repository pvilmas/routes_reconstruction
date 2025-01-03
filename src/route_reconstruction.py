import xml.etree.ElementTree as ET
import json 
import sys

def parse_routes_from_xml(filename:str) -> dict:
    """
    Parse vehicle routes from a .rou.xml file.

    Args:
        filename: the path to the .rou.xml file.

    Returns:
        A dictionary mapping vehilce IDs to their routes
    """
    routes = {}
    try:
        tree = ET.parse(filename)
        root = tree.getroot()

        for vehicle in root.findall("vehicle"):
            vehicle_id = vehicle.get("id")
            route_element = vehicle.find("route")

            if vehicle_id and route_element is not None:
                edges = route_element.get("edges","")
                routes[vehicle_id] = edges
    except Exception as e:
        print(f'Error parsing XML file {filename}: {e}')

    return routes


def align_segments_to_partitions(vehicle_id:str, original_edges_list:list, edge_to_partition:dict) -> list:
    """
    Aligns segments of routes to the corresponding partition

    Args:
        vehicle_id: the id of the vehicle/route
        original_edges_list: a list containing the edges of the original route
        edge_to_partition: a dictionary mapping edges to partitions

    Returns: a list of aligned segments
    """
    segments = []
    current_partition = None
    current_segment = []

    for edge in original_edges_list:
        partitions = edge_to_partition.get(edge, None)
        
        if not partitions:
            print(f'Warning: Edge {edge} for vehicle {vehicle_id} not found in any partition.')
            continue

        if current_partition is None:
            current_partition = next(iter(partitions))
        
        if current_partition not in partitions:
            segments.append((current_partition, current_segment))
            current_partition = next(iter(partitions))
            current_segment = []

        current_segment.append(edge)
    
    if current_segment:
        segments.append((current_partition,current_segment))
    return segments


def reconstruct_routes(original_routes:dict, partitioned_routes:dict) -> dict:
    """
    Reconstruct routes into the specified JSON format.

    Args:
        original_routes: a dictionary of original vehicle routes
        partitioned_routes: a dictionary of partitioned vehicle routes (partition -> {vehicle_id -> cut_route})
    
    Returns:
        A dictionary representing the reconstructed routes in JSON format.
    """
    reconstructed_routes = {"routes": []}

    edge_to_partition = {}
    for partition_id, vehicles in partitioned_routes.items():
        for vehicle_id, edges in vehicles.items():
            for edge in edges.split():
                if edge not in edge_to_partition:
                    edge_to_partition[edge] = set()
                edge_to_partition[edge].add(partition_id)

    for vehicle_id, original_edges in original_routes.items():
        original_edges_list = original_edges.split(" ")
        segments = align_segments_to_partitions(vehicle_id, original_edges_list, edge_to_partition)
        cut_routes = []

        for i, (partition_id, edges) in enumerate(segments):
                next_partition = -1
                next_route = ""

                if i + 1 < len(segments):
                    next_partition = segments[i+1][0]
                    next_route = " ".join(segments[i+1][1])
                
                cut_routes.append({
                    "partition": partition_id,
                    "id": vehicle_id,
                    "cut_route": " ".join(edges),
                    "next_partition": next_partition,
                    "next_route": next_route
                })
       
        reconstructed_routes["routes"].append({
            "original_route": original_edges,
            "cut_routes": cut_routes
        })
    return reconstructed_routes


def save_to_json(data:dict, filename:str) -> None:
    """
    Save data to a JSON file.

    Args:
        data: the data save.
        filename: the output JSON filename
    """
    try:
        with open(filename, "w") as file:
            json.dump(data, file, indent=4)
    except Exception as e:
        print(f'Error saving JSON file {filename}: {e}')

if __name__ == "__main__":
    if len(sys.argv) < 4:
        print("Usage python3 route_reconstruction.py <output.json> <original.rou.xml> [<partition1.rou.xml> ...]")
        sys.exit(1)

    output_file = sys.argv[1]
    osm_file = sys.argv[2]
    partition_files = sys.argv[3:]

    original_routes = parse_routes_from_xml(osm_file)
    partitioned_routes = {}

    for i, partition_file in enumerate(partition_files):
        partitioned_routes[i] = parse_routes_from_xml(partition_file)
    
    reconstructed_routes = reconstruct_routes(original_routes, partitioned_routes)

    save_to_json(reconstructed_routes, output_file)

    print(f'Reconstructed routes saved successfully to {output_file}.')