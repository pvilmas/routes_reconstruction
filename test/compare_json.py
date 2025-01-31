# import a json file as a dictionary a compare to another
import json

def ordered(obj):
    """
    Order a JSON object.

    Args:
        obj: the JSON object to order
    
    Returns:
        The ordered JSON object.
    """
    if isinstance(obj, dict):
        return sorted((k, ordered(v)) for k, v in obj.items())
    if isinstance(obj, list):
        return sorted(ordered(x) for x in obj)
    else:
        return obj


def compare_json(file1:str, file2:str) -> bool:
    """
    Compare two JSON files.

    Args:
        file1: the first JSON file
        file2: the second JSON file
    
    Returns:
        True if the files are equal, False otherwise.
    """
    with open(file1, 'r') as f:
        data1 = json.load(f)
    with open(file2, 'r') as f:
        data2 = json.load(f)
    
    return ordered(data1) == ordered(data2)
    

if __name__ == "__main__":
    json_cpp = "routes/output_cpp.json"
    json_py = "routes/output_py.json"
    print(compare_json(json_cpp, json_py))