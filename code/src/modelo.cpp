/* Demo_03_Model.cpp */

#include <stdio.h>
#include <vector>
#include <regex>
#include <fstream>
#include <iostream>
#include <boost/mpi.hpp>
#include "repast_hpc/AgentId.h"
#include "repast_hpc/RepastProcess.h"
#include "repast_hpc/Utilities.h"
#include "repast_hpc/Properties.h"
#include "repast_hpc/initialize_random.h"
#include "repast_hpc/SVDataSetBuilder.h"
#include "repast_hpc/Point.h"

#include "modelo.h"

Modelo::Modelo(std::string propsFile, int argc, char** argv, boost::mpi::communicator* comm): context(comm) {
	props = new repast::Properties(propsFile, argc, argv, comm);
	stopAt = repast::strToInt(props->getProperty("stop.at"));
	countOfAgents = repast::strToInt(props->getProperty("count.of.agents"));
	initializeRandom(*props, comm);
	
	// Toda la parte del mapa
	std::string mapa_path = argv[3];       // Path al mapa
	std::ifstream mapa_file (mapa_path);
	std::string linea;

	int ancho, alto;

	if ( mapa_file.is_open() ) {

		// Procesa la primer linea para sacar las dimensiones del mapa
		mapa_file >> linea;
		
		std::regex linea_tamano("([0-9]+)x([0-9]+)");
		std::smatch match;
		std::regex_match(linea, match, linea_tamano);

		ancho = std::stoi(match[1]);
		alto = std::stoi(match[2]);
		
		std::cout << "Dimensiones del mapa: " << ancho << "," << alto << std::endl;
	} else {
		std::cout << "Archivo no abierto: " << std::endl;
	}

	// TODO Mover el archivo a miembro ineterno, y cerrarlo después de que se
	// carguen los agentes, ahora está cargando dos agentes feos a manopla
	mapa_file.close();

    repast::Point<double> origin(0, 0);
    repast::Point<double> extent( static_cast<double>(ancho), static_cast<double>(alto));
    
    repast::GridDimensions gd(origin, extent);
    
	// Nota esto estaba en 2, creemos que es el spliteo
    std::vector<int> processDims;
    processDims.push_back(1);
    processDims.push_back(1);
    
    discreteSpace = new repast::SharedDiscreteSpace<Agente, repast::StrictBorders, repast::SimpleAdder<Agente> >("AgentDiscreteSpace", gd, processDims, 0, comm);
	
    std::cout << "RANK " << repast::RepastProcess::instance()->rank() << " BOUNDS: " << discreteSpace->bounds().origin() << " " << discreteSpace->bounds().extents() << std::endl;
    
   	context.addProjection(discreteSpace);
}


Modelo::~Modelo(){
	delete props;
}

void Modelo::init(){
	int rank = repast::RepastProcess::instance()->rank();
	for(int i = 0; i < countOfAgents; i++){
        repast::Point<int> initialLocation((int)discreteSpace->dimensions().origin().getX() + i,(int)discreteSpace->dimensions().origin().getY() + i);
		repast::AgentId id(i, rank, 0);
		id.currentRank(rank);

		// Crea agentes, los primero 10 enfermos, el resto sanos
		Agente * agent;
		if ( i < 10 ) agent = new Agente(id, 0.8, 0.2, true);
		else agent = new Agente(id, 0.8, 0.2, false);

		context.addAgent(agent);
        discreteSpace->moveTo(id, initialLocation);
	}
}

void Modelo::doSomething(){
	int whichRank = 0;
	
	std::cout << "[ TICK " << repast::RepastProcess::instance()->getScheduleRunner().currentTick() << " ] ";

	// Imprime la ubicación de todos los agentes, y su tipo (enfermo, sano)
	for (int i = 0; i < countOfAgents; i++ ) {

		repast::AgentId agente_id(i, 0, 0);						// Genera el ID del agente
		Agente * agente_a_mostrar = context.getAgent(agente_id);// Obtiene un puntero al agente
		std::vector<int> ubicacion_ag;							// Obtiene la ubicación del agente
		discreteSpace->getLocation(agente_id, ubicacion_ag);
		
		std::cout << i << ";" << agente_a_mostrar->get_tipo() << ";" << ubicacion_ag[0] << ";" << ubicacion_ag[1] << ";"; // Imprime el ID del agente, coordenada x, y, y tipo
	}

	std::cout << std::endl;

	std::vector<Agente*> agents;
	context.selectAgents(repast::SharedContext<Agente>::LOCAL, countOfAgents, agents);
	std::vector<Agente*>::iterator it = agents.begin();
	while(it != agents.end()){
        (*it)->play(&context, discreteSpace);
		it++;
    }

    it = agents.begin();
    while(it != agents.end()){
		(*it)->move(discreteSpace);
		it++;
    }
}

void Modelo::initSchedule(repast::ScheduleRunner& runner){
	runner.scheduleEvent(1, 1, repast::Schedule::FunctorPtr(new repast::MethodFunctor<Modelo> (this, &Modelo::doSomething)));
	runner.scheduleEndEvent(repast::Schedule::FunctorPtr(new repast::MethodFunctor<Modelo> (this, &Modelo::recordResults)));
	runner.scheduleStop(stopAt);
	
}

void Modelo::recordResults(){
	if(repast::RepastProcess::instance()->rank() == 0){
		props->putProperty("Result","Passed");
		std::vector<std::string> keyOrder;
		keyOrder.push_back("RunNumber");
		keyOrder.push_back("stop.at");
		keyOrder.push_back("Result");
		props->writeToSVFile("./output/results.csv", keyOrder);
    }
}


	
