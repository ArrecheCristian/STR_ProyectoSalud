#!/bin/sh

CORES="1"
OUTPUT_FILE="$2"
mpirun -n $CORES ../bin/repast.exe ../props/config.props ../props/model.props $1 > $2