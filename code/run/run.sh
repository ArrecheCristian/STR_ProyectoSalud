#!/bin/sh

CORES="1"
OUTPUT_FILE="salida.txt"
mpirun -n $CORES ../bin/repast.exe ../props/config.props ../props/model.props ./mapa #> "$OUTPUT_FILE"