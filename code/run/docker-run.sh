#!/bin/bash

docker run -it --mount source=$PWD/../,destination=/home/user/source/src,type=bind martinparadiso/rhpc:latest bash