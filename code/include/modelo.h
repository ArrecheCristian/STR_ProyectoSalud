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

/* Agent Package Provider */
class AgentePackageProvider {
	
private:
    repast::SharedContext<Agente>* agents;
	
public:
	
    AgentePackageProvider(repast::SharedContext<Agente>* agentPtr);
	
    void providePackage(Agente * agent, std::vector<AgentePackage>& out);
	
    void provideContent(repast::AgentRequest req, std::vector<AgentePackage>& out);
	
};

/* Agent Package Receiver */
class AgentePackageReceiver {
	
private:
    repast::SharedContext<Agente>* agents;
	
public:
	
    AgentePackageReceiver(repast::SharedContext<Agente>* agentPtr);
	
    Agente * createAgent(AgentePackage package);
	
    void updateAgent(AgentePackage package);
	
};


/* Data Collection */
class DataSource_AgentTotals : public repast::TDataSource<int>{
private:
	repast::SharedContext<Agente>* context;

public:
	DataSource_AgentTotals(repast::SharedContext<Agente>* c);
	int getData();
};
	

class DataSource_AgentCTotals : public repast::TDataSource<int>{
private:
	repast::SharedContext<Agente>* context;
	
public:
	DataSource_AgentCTotals(repast::SharedContext<Agente>* c);
	int getData();
};

class RepastHPCDemoModel{
	int stopAt;
	int countOfAgents;
	repast::Properties* props;
	repast::SharedContext<Agente> context;
	
	AgentePackageProvider* provider;
	AgentePackageReceiver* receiver;

	repast::SVDataSet* agentValues;
    repast::SharedDiscreteSpace<Agente, repast::StrictBorders, repast::SimpleAdder<Agente> >* discreteSpace;
	
public:
	RepastHPCDemoModel(std::string propsFile, int argc, char** argv, boost::mpi::communicator* comm);
	~RepastHPCDemoModel();
	void init();
	void requestAgents();
	void cancelAgentRequests();
	void removeLocalAgents();
	void doSomething();
	void initSchedule(repast::ScheduleRunner& runner);
	void recordResults();
};

#endif
