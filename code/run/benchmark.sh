#!/bin/bash

mapa="mapa_50x50_500"
cores="4"
iteraciones="1"

echo "Ejecutando mapa $mapa"

for (( i = 0; i < iteraciones; i++ )); do

    time mpiexec -n $cores ../bin/repast.exe ../props/config.props ../props/model.props $mapa

done