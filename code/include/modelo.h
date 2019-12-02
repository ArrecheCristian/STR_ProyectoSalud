/* Demo_03_Model.h */

#ifndef DEMO_03_MODEL
#define DEMO_03_MODEL

#include <boost/mpi.hpp>
#include "repast_hpc/Schedule.h"
#include "repast_hpc/Properties.h"
#include "repast_hpc/SharedContext.h"
#include "repast_hpc/AgentRequest.h"
#include "repast_hpc/TDataSource.h"
#include "repast_hpc/SVDataSet.h"
#include "repast_hpc/SharedDiscreteSpace.h"
#include "repast_hpc/GridComponents.h"

#include "agente.h"

class Modelo {
	int stopAt;
	int countOfAgents;
	repast::Properties* props;
	repast::SharedContext<Agente> context;

    repast::SharedDiscreteSpace<Agente, repast::StrictBorders, repast::SimpleAdder<Agente> >* discreteSpace;
	
public:
	Modelo(std::string propsFile, int argc, char** argv, boost::mpi::communicator* comm);
	~Modelo();
	void init();
	void doSomething();
	void initSchedule(repast::ScheduleRunner& runner);
	void recordResults();
};

#endif
