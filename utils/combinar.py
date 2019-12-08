#!/usr/bin/python3

from contextlib import ExitStack
import argparse                 # Herramienta para parsear los argumentos

# Configuración para parsear los argumentos ===================================

# Crea el parser y define todos los argumentos necesarios
parser = argparse.ArgumentParser(epilog="Script para combinar los archivos de salida de N process")

parser.add_argument("salida_out",type=str, help="Nombre del archivo de saldia")
parser.add_argument("salidas", nargs='+', type=str, help="N archivos que contienen los resultados de la simulacion.")

args = parser.parse_args()

# Codigo posta ================================================================

with open(args.salida_out, "w") as arch_salida:
    with ExitStack() as stack:

        files = [ stack.enter_context(open(fname)) for fname in args.salidas ]

        for line in files[0]:
            arch_salida.write(line.rstrip())
            for archs_restantes in files[1:]:
                arch_salida.write( archs_restantes.readline().rstrip() )
            arch_salida.write("\n")


arch_salida.close()