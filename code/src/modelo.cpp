/* Demo_03_Model.cpp */

#include <stdio.h>
#include <vector>
#include <boost/mpi.hpp>
#include "repast_hpc/AgentId.h"
#include "repast_hpc/RepastProcess.h"
#include "repast_hpc/Utilities.h"
#include "repast_hpc/Properties.h"
#include "repast_hpc/initialize_random.h"
#include "repast_hpc/SVDataSetBuilder.h"
#include "repast_hpc/Point.h"

#include "modelo.h"

Modelo::Modelo(std::string propsFile, int argc, char** argv, boost::mpi::communicator* comm): context(comm){
	props = new repast::Properties(propsFile, argc, argv, comm);
	stopAt = repast::strToInt(props->getProperty("stop.at"));
	countOfAgents = repast::strToInt(props->getProperty("count.of.agents"));
	initializeRandom(*props, comm);
	
    repast::Point<double> origin(-100,-100);
    repast::Point<double> extent(200, 200);
    
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


	
