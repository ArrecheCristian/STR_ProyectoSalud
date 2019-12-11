#!/bin/bash

mapa="mapa_50x50_500"
cores="1"
iteraciones="5"

echo "Ejecutando mapa $mapa"

for (( i = 0; i < iteraciones; i++ )); do

    time mpiexec -n $cores ../bin/repast.exe ../props/config.props ../props/model.props $mapa

done