#!/usr/bin/python3

import argparse                 # Herramienta para parsear los argumentos
from PIL import Image           # Herramienta para manipulación de imágenes

# Configuración para parsear los argumentos ===================================

# Crea el parser y define todos los argumentos necesarios
parser = argparse.ArgumentParser(epilog="Script para generar imágenes de un mapa, como así también de la secuencia de una simulación")

parser.add_argument("plano", help="Archivo que contiene la estructura del plano.")
parser.add_argument("datos", nargs='?', help="Archivo que contiene los resultados de la simulación, para poder generar las imágenes de los agentes.")

parser.add_argument("-t", "--ticks", default=-1, type=int, help="Numero de ticks a graficar")
parser.add_argument("-p", "--prefix", default="image-", type=str, help="Prefijo para el nombre de los archivos de salida")

args = parser.parse_args()

# Configuración de las imágenes ===============================================

# Diccionario que contiene todos los assets/imágenes
assets = [
    Image.open("assets/fondo.png"),             # 0
    Image.open("assets/pared.png"),             # 1
    Image.open("assets/persona_sana.png"),      # 2
    Image.open("assets/persona_enferma.png")    # 3
]

assets_size = (32, 32)                                  # Tamaño de los assets

map_temp = [ [ 1, 1, 1, 1 ],                            # Mapa temporal de prueba
             [ 1, 2, 3, 1 ],
             [ 0, 0, 0, 1 ],
             [ 1, 0, 3, 1 ],
             [ 1, 1, 1, 1 ]]

map_size_units = ( len(map_temp[0]), len(map_temp) )
map_size_px = ( map_size_units[0] * assets_size[0], map_size_units[1] * assets_size[1])     # Tamaño del mapa TODO ahora está forzado a mano, pero habría que levantarlo del archivo de mapa

# Genera una imágen de prueba
imagen = Image.new('RGB', map_size_px)

for y in range(0, map_size_units[1] ):
    for x in range(0, map_size_units[0] ):
        coordenada = ( assets_size[0] * x , assets_size[1] * y) 
        imagen.paste( assets[ map_temp[y][x] ], coordenada )    # Por un tema técnico se guarda primero fila y después columna

imagen.save("prueba.jpg", "JPEG")