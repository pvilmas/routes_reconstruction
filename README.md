# Módulo de reconstrucción de rutas particionadas con cutRoutes.py de SUMO en Python porteado a C++

## Descripción

El script de Python `route_reconstruction.py` consiste en un módulo que toma rutas que fueron particionadas por la herramienta cutRoutes.py de SUMO (https://sumo.dlr.de/docs/Tools/Routes.html#cutroutespy , 
el código fuente de la herramienta se puede encontrar en: https://github.com/eclipse-sumo/sumo/blob/main/tools/route/cutRoutes.py). Recibe los archivos XML correspondientes a las descripciones
de rutas de tráfico urbano y retorna un JSON con las rutas ordenadas según su ruta original, indicando el id del vehículo, la partición a la que corresponde el segmento de ruta, y la ruta y partición
que va a continuación.

El código de este repositorio es un porteo a C++ del script original de Python, con el objetivo de mejorar la eficiencia en la reconstrucción de rutas particionadas. Sin embargo, a pesar de entregar el mismo output, se empeoró la eficiencia del programa, lo cual se deja para futuras mejoras de optimización. Al final del README se detallan los resultados de la comparación de eficiencia entre ambos scripts y se proponen futuras mejoras.

## Requisitos

Ambos código de Python y C++ fueron ejecutados en Debian 11 y necesitan de lo siguiente:

- Compilador de C++: g++ 10.2.1
- Python 3.9.2
- Bibliotecas de Python: xml.etree.ElementTree, json, sys, os, time
- Bibliotecas de C++: iostream, fstream, string, vector, map, nlohmann/json (incluida para el manejo de json), pugixml (incluida para el manejo de xml)

## Uso

Para las ejecuciones de los archivos sean más simples se adjunta un makefile con las instrucciones más usadas:

- `make`: compila el código de C++ y genera el ejecutable `routeReconstruction.out`.
- `make run`: ejecuta el código de C++ con los archivos de entrada xml y genera el archivo de salida `output_cpp.json`. Si se quiere probar con otras rutas y sus particiones es necesario modificar este instrucción.
- `make run_py`: ejecuta el código de Python con los archivos de entrada xml y genera el archivo de salida `output_py.json`. Si se quiere probar con otras rutas y sus particiones es necesario modificar este instrucción.
- `make test`: compila los tests para todas las funciones del código de C++ escritas en el archivo `utilTest.cpp`.
- `make test_run`: ejecuta los tests compilados con el comando anterior.

## Resultados

El código de C++ entrega el mismo json que el código en Python pero en desorden, para comprobar esto se creó la función `compare_json(file1:str, file2:str) -> bool` en el archivo `test/compare_json.py`, la cual primero ordena los json y luego los compara, se puede probar ejecutando `python test/compare_json.py`, si los json son iguales se imprimirá `True` en la consola.

Sin embargo, al ejecutar ambos códigos, el que escrito en C++ llega incluso a ejecutarse más de 10 veces más lento que el código en Python, se puede probar esto corriendo ambos códigos con sus comandos respectivos ya que los tiempos de ejecución de cada uno se registran en `cpp_time.txt` y `python_time.txt`.

## Futuras mejoras

Para mejorar la eficiencia del código en C++ se proponen las siguientes mejoras:

- **Recortar librerías**: Se pueden recortar las librerías incluidas en el código, esto es, solo incluir las funciones que se van a utilizar y no todas las funciones de la librería, en especial para `pugixml`.

- **Optimización de estructuras de datos**: Puede que ``vector`` no sea óptimo para el manejo de listas de strings, e incluso tal vez sea mejor usar `char*` en vez de `std::string`.