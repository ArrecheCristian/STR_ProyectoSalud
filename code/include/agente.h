/* Demo_03_Agent.h */

#ifndef DEMO_03_AGENT
#define DEMO_03_AGENT

#include "repast_hpc/AgentId.h"
#include "repast_hpc/SharedContext.h"
#include "repast_hpc/SharedDiscreteSpace.h"


/* Agents */
class Agente {
	
private:
    repast::AgentId _id;
    
    const float _prob_contagiar;
    const float _prob_ser_contagiado;
	bool _enfermo;

public:

    Agente(repast::AgentId id, const float prob_contagiar, const float prob_ser_contagiado, const bool enfermo);
	
    ~Agente();
	
    /* Required Getters */
    virtual repast::AgentId& getId(){                   return _id;    }
    virtual const repast::AgentId& getId() const {      return _id;    }
	
    /* Getters specific to this kind of Agent */
    float get_prob_contagiar() const { return _prob_contagiar; }
    float get_prob_ser_contagiado() const { return _prob_ser_contagiado; }

    /* Actions */
    void play(repast::SharedContext<Agente>* context,
              repast::SharedDiscreteSpace<Agente, repast::StrictBorders, repast::SimpleAdder<Agente> >* space);    // Choose three other agents from the given context and see if they cooperate or not
    void move(repast::SharedDiscreteSpace<Agente, repast::StrictBorders, repast::SimpleAdder<Agente> >* space);

    // Funciones para interaccion entre agentes

    /**
     * Trata de enfermar al agente en base a una probabilidad interna
     */
    void contagiar();
    
};

/* Serializable Agent Package */
struct AgentePackage {
	
public:
    int    id;
    int    rank;
    int    type;
    int    currentRank;
    double c;
    double total;
	
    /* Constructors */
    AgentePackage(); // For serialization
    AgentePackage(int _id, int _rank, int _type, int _currentRank, double _c, double _total);
	
    /* For archive packaging */
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version){
        ar & id;
        ar & rank;
        ar & type;
        ar & currentRank;
        ar & c;
        ar & total;
    }
	
};


#endif