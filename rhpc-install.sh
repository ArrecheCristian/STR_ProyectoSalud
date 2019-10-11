#!/bin/bash

INSTALL_FOLDER="~/rhpc"

# Paquetes necesarios de APT
pkg="git gcc make cmake libopenmpi-dev libopenmpi-dev wget tar diffutils libboost-all-dev"

# Instala los paquetes necesarios
sudo apt-get update -y && sudo apt-get install -y $pkg

# Crea la carpeta de repast
mkdir $INSTALL_FOLDER
cd $INSTALL_FOLDER

# Descarga los instaladores de Repast y el SRC de ejemplo
wget 'https://repast.github.io/hpc_tutorial/SRC.tar.gz'
wget 'https://github.com/Repast/repast.hpc/releases/download/v2.3.0/repast_hpc-2.3.0.tgz' -o repast_script.tgz

# Extrae ambos
tar -xvf SRC.tar.gz .
tar -xvf repast_script

# Instala Repast
cd repast_script/MANUAL_INSTALL
./install.sh curl
./install.sh netcdf
./install.sh boost
./install.sh rhpc

# Reemplaza las variables del env
env="""
BOOST_INCLUDE=-I~/sfw/Boost/Boost_1.61/include
BOOST_LIB_DIR=-L~/sfw/Boost/Boost_1.61/lib
BOOST_LIBS=-lboost_mpi-mt -lboost_serialization-mt -lboost_system-mt -lboost_filesystem-mt

REPAST_HPC_INCLUDE=-I~/sfw/repast_hpc-2.3.0/include/repast_hpc
REPAST_HPC_LIB_DIR=-L~/sfw/repast_hpc-2.3.0/lib
REPAST_HPC_LIB=-lrepast_hpc-2.3.0
"""

# Limpia los archivos
rm -r repast_script repast_script.tgz SRC.tar.gz
