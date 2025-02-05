#!/usr/bin/python3

import argparse                 # Herramienta para parsear los argumentos
from PIL import Image           # Herramienta para manipulación de imágenes
import re
import copy

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

# Carga el mapa
mapa = [ ]

with open(args.plano, "r") as f:
    primer_linea = f.readline()
    ancho = re.match("(?P<ancho>[0-9]+)x(?P<alto>[0-9]+)", primer_linea )["ancho"]
    alto = re.match("(?P<ancho>[0-9]+)x(?P<alto>[0-9]+)", primer_linea )["alto"]
    map_size_units = (int(ancho), int(alto))

    y = 0
    for linea in f:
        fila = re.findall("[0-9]+[ \n]", linea)
        mapa.append([])    # Por temas de python hay que inicializar el vector

        for columna in fila:
            tipo = int(columna)

            # Si no se paso información de la simulación dibuja a las personas,
            # no tiene sentido hacerlo si se pasan los ticks, ya que esas personas
            # son solo válidas para el instante incial
            if not args.datos:
                mapa[y].append(tipo)
            else:
                if tipo < 2:
                    mapa[y].append(tipo)
                else:
                    mapa[y].append(0)
                     
            
        y += 1


map_size_px = ( map_size_units[0] * assets_size[0], map_size_units[1] * assets_size[1])

# Genera una imágen de prueba
imagen = Image.new('RGB', map_size_px)

# TODO si recibe tamibien un archivo de datos, procesar cada
# tick y en cada tick generar una imágen diferente a partir del
# mismo fondo+pared

for y in range(0, map_size_units[1] ):
    for x in range(0, map_size_units[0] ):
        print(mapa[y][x], end=" ")

        imagen.paste( assets[ mapa[y][x] ], (x * assets_size[0], y * assets_size[1]) )

    print()
    
    imagen.save("img_base.jpg", "JPEG")

# Si recibe datos, los grafica
if args.datos:

    print("Hay datos")

    with open(args.datos, "r") as arch_datos:
        n = 0

        for linea in arch_datos:
            imagen_n = copy.deepcopy(imagen)
            linea_de_info = False

            regex="rank=([0-9]+),id=([0-9]+),tipo=([-0-9]+),x=([-0-9]+),y=([-0-9]+);"
            for agente in re.findall(regex, linea):
                linea_de_info = True
                print(agente)
                x = int(agente[3])
                y = int(agente[4])
                tipo = int(agente[2])
                imagen_n.paste( assets[tipo], (x * assets_size[0], y * assets_size[1]) )

            if linea_de_info:
                n += 1
                imagen_n.save(f"img{n:03d}.jpg", "JPEG")