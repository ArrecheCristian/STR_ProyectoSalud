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
	



.PHONY: repast
repast: 
	$(MPICXX) $(REPAST_HPC_DEFINES) $(BOOST_INCLUDE) $(REPAST_HPC_INCLUDE) -I./include -c ./src/main.cpp -o ./objects/main.o
	$(MPICXX) $(REPAST_HPC_DEFINES) $(BOOST_INCLUDE) $(REPAST_HPC_INCLUDE) -I./include -c ./src/modelo.cpp -o ./objects/modelo.o
	$(MPICXX) $(REPAST_HPC_DEFINES) $(BOOST_INCLUDE) $(REPAST_HPC_INCLUDE) -I./include -c ./src/agente.cpp -o ./objects/agente.o
	$(MPICXX) $(REPAST_HPC_DEFINES) $(BOOST_INCLUDE) $(REPAST_HPC_INCLUDE) -I./include -c ./src/plano.cpp -o ./objects/plano.o
	$(MPICXX) $(BOOST_LIB_DIR) $(REPAST_HPC_LIB_DIR) -o ./bin/repast.exe  ./objects/main.o ./objects/modelo.o ./objects/agente.o ./objects/plano.o $(REPAST_HPC_LIB) $(BOOST_LIBS)


