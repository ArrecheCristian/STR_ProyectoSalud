#************************************************************************************************************
#
# Repast HPC Tutorial Makefile
#
#************************************************************************************************************

include ./env

.PHONY: all
all : 


.PHONY: clean_output_files
clean_output_files:
	rm -f *.csv
	rm -f *.txt
	rm -f ./output/*.csv
	rm -f ./output/*.txt
	rm -f ./logs/*.*

.PHONY: clean_compiled_files
clean_compiled_files:
	rm -f *.exe
	rm -f ./bin/*.exe
	rm -f *.o
	rm -f ./object/*.o
	



.PHONY: repast
repast: clean_compiled_files
	$(MPICXX) $(REPAST_HPC_DEFINES) $(BOOST_INCLUDE) $(REPAST_HPC_INCLUDE) -I./include -c ./src/Demo_03_Main.cpp -o ./objects/Demo_03_Main.o
	$(MPICXX) $(REPAST_HPC_DEFINES) $(BOOST_INCLUDE) $(REPAST_HPC_INCLUDE) -I./include -c ./src/Demo_03_Model.cpp -o ./objects/Demo_03_Model.o
	$(MPICXX) $(REPAST_HPC_DEFINES) $(BOOST_INCLUDE) $(REPAST_HPC_INCLUDE) -I./include -c ./src/Demo_03_Agent.cpp -o ./objects/Demo_03_Agent.o
	$(MPICXX) $(BOOST_LIB_DIR) $(REPAST_HPC_LIB_DIR) -o ./bin/Demo_03.exe  ./objects/Demo_03_Main.o ./objects/Demo_03_Model.o ./objects/Demo_03_Agent.o $(REPAST_HPC_LIB) $(BOOST_LIBS)


