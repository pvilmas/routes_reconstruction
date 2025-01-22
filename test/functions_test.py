import sys
import os
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), os.path.pardir, 'src')))

import route_reconstruction as rr
import time

def test_time_parse_routes_from_xml():
    osm_file = 'routes/viladecans.rou.xml'
    t_i = time.time()
    routes = rr.parse_routes_from_xml(osm_file)
    t_f = time.time()

    print(f'parse_routes_from_xml: {t_f - t_i} seconds')

def test_time_align_segments_to_partitions():
    pass