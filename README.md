# Módulo de reconstrucción de rutas particionadas con cutRoutes.py de SUMO
El script de Python `route_reconstruction.py` consiste en un módulo que toma rutas que fueron particionadas por la herramienta cutRoutes.py de SUMO (https://sumo.dlr.de/docs/Tools/Routes.html#cutroutespy , 
el código fuente de la herramienta se puede encontrar en: https://github.com/eclipse-sumo/sumo/blob/main/tools/route/cutRoutes.py). Recibe los archivos XML correspondientes a las descripciones
de rutas de tráfico urbano y retorna un JSON con las rutas ordenadas según su ruta original, indicando el id del vehículo, la partición a la que corresponde el segmento de ruta, y la ruta y partición
que va a continuación.

Para ejecutar el código desde una terminal se debe invocar de la siguiente manera:

`python routes_reconstruction.py <output.json> <original.rou.xml> [<partition_1.rou.xml> ... <partition_n.rou.xml>]`
