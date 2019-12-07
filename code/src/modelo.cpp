/* Demo_03_Model.cpp */

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
#include "plano.h"

Modelo::Modelo(std::string propsFile, int argc, char** argv, boost::mpi::communicator* comm): context(comm), _mapa_archivo(argv[3] ), _cant_agentes_act(0) {
	props = new repast::Properties(propsFile, argc, argv, comm);
	stopAt = repast::strToInt(props->getProperty("stop.at"));
	countOfAgents = repast::strToInt(props->getProperty("count.of.agents"));
	initializeRandom(*props, comm);
	
	// Toda la parte del mapa
	std::string linea;

	int ancho, alto;

	if ( _mapa_archivo.is_open() ) {

		// Procesa la primer linea para sacar las dimensiones del mapa
		_mapa_archivo >> linea;
		
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
	
	//mapa_file.close();		//Dejamos el archivo abierto para seguir leyendolo desde el init()

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

	// Crea el plano
	_plano = new Plano(ancho, alto);
}

Modelo::~Modelo(){
	delete props;
	delete _plano;
}

void Modelo::init(){


	int rank = repast::RepastProcess::instance()->rank();

	for ( int y = 0; y < _plano->get_alto() ; y++ ) {
		
		int x = 0;
		
		for (int x = 0; x < _plano->get_ancho(); x++) {
			int tipo;
			_mapa_archivo >> tipo;

			// Imprime el tipo que encontró
			std::cout << tipo << " ";
			
			// Si es una pared, le indica al mapa que ahí hay una pared
			if ( tipo == 1 ) _plano->set_pared(x, y);

			// Si es un agente, lo crea
			else if ( tipo >= 2 ) {

				repast::Point<int> initialLocation(x,y);
				repast::AgentId id(_cant_agentes_act++, rank, 0);
				id.currentRank(rank);
				
				Agente * agent;
				agent = new Agente(id, 0.8, 0.2, tipo);
				context.addAgent(agent);
        		discreteSpace->moveTo(id, initialLocation);
			}
	
		} // for columna

		std::cout << std::endl;

	} // for fila

	_mapa_archivo.close();
}

void Modelo::doSomething(){
	int whichRank = 0;
	
	std::cout << "[ TICK " << repast::RepastProcess::instance()->getScheduleRunner().currentTick() << " ] ";

	// Imprime la ubicación de todos los agentes, y su tipo (enfermo, sano)
	for (int i = 0; i < _cant_agentes_act; i++ ) {

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
		(*it)->move(discreteSpace, _plano);
		it++;
    }
}

void Modelo::initSchedule(repast::ScheduleRunner& runner){
	runner.scheduleEvent(1, 1, repast::Schedule::FunctorPtr(new repast::MethodFunctor<Modelo> (this, &Modelo::doSomething)));
	runner.scheduleEndEvent(repast::Schedule::FunctorPtr(new repast::MethodFunctor<Modelo> (this, &Modelo::recordResults)));
	runner.scheduleStop(stopAt);
	
}

void Modelo::recordResults(){

	std::cout << "[ TICK " << repast::RepastProcess::instance()->getScheduleRunner().currentTick() << " ] ";

	// Imprime la ubicación de todos los agentes, y su tipo (enfermo, sano)
	for (int i = 0; i < _cant_agentes_act; i++ ) {

		repast::AgentId agente_id(i, 0, 0);						// Genera el ID del agente
		Agente * agente_a_mostrar = context.getAgent(agente_id);// Obtiene un puntero al agente
		std::vector<int> ubicacion_ag;							// Obtiene la ubicación del agente
		discreteSpace->getLocation(agente_id, ubicacion_ag);
		
		std::cout << i << ";" << agente_a_mostrar->get_tipo() << ";" << ubicacion_ag[0] << ";" << ubicacion_ag[1] << ";"; // Imprime el ID del agente, coordenada x, y, y tipo
	}

	std::cout << std::endl;
	
	if(repast::RepastProcess::instance()->rank() == 0){
		props->putProperty("Result","Passed");
		std::vector<std::string> keyOrder;
		keyOrder.push_back("RunNumber");
		keyOrder.push_back("stop.at");
		keyOrder.push_back("Result");
		props->writeToSVFile("./output/results.csv", keyOrder);
    }
}


	
