import argparse
import random

# Configuración para parsear los argumentos ===================================

# Crea el parser y define todos los argumentos necesarios
parser = argparse.ArgumentParser(epilog="Script para generar imágenes un mapa de NxM, paredes en los bordes y agentes aleatorios")

parser.add_argument("x", type=int, help="Ancho del mapa")
parser.add_argument("y", type=int, help="Alto del mapa")
parser.add_argument("salida", type=str, help="path del archivo de salida")

parser.add_argument("-p", "--probabilidad", default=0.05, type=float, help="Probabilidad de que un punto sea un agente")
parser.add_argument("-e", "--enfermo", default=0.5, type=float, help="Probabilidad de que un agente sea enfermo")

args = parser.parse_args()

# Inicializa el random
with open(args.salida, "w") as arch:
    for y in range(0, args.y):
        for x in range(0, args.x):
            
            if ( x == 0 or x == args.x - 1 or y == 0 or y == args.y - 1):   # Si es un borde
                arch.write("1 ")                                        # pone una pared
            
            else:                                                       # Si no es un borde
                if ( args.probabilidad > random.random() ):      # Tratar de hacer un agente
                    if ( args.enfermo > random.random() ):      # Tratar de generar un enfermo
                        arch.write("3 ")
                    else:                                   # Si no lo pudo enfermar, lo genera sano
                        arch.write("2 ")
                
                else:
                    arch.write("0 ")                    # Si no pudo hacer un agente, deja vacio 
        
        arch.write("\n")        # Pasa a la siguiente fila

arch.close()