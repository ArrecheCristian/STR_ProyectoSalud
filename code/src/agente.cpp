/* Demo_03_Agent.cpp */

#include <iostream>

#include "agente.h"
#include "repast_hpc/Moore2DGridQuery.h"
#include "repast_hpc/VN2DGridQuery.h"
#include "repast_hpc/Point.h"

#include "plano.h"

Agente::Agente(const repast::AgentId id, const float prob_contagio, const float prob_ser_contagiado, const int tipo) 
    :   _id{id},
        _prob_contagiar{prob_contagio},
        _prob_ser_contagiado{prob_ser_contagiado},
        _enfermo{ tipo == 3 ? true : false } { }

Agente::~Agente() { }

void Agente::play(repast::SharedContext<Agente>* context,
                  repast::SharedDiscreteSpace<Agente, repast::StrictBorders, repast::SimpleAdder<Agente> >* space){

    // Trata de contagiarse de sus adyacente solo si no está enfermo
    if ( ! _enfermo ) {
        
        std::vector<Agente *> agentes_adyacentes;
        std::vector<int> ubicacion_agente;

        // Obtiene la ubicación actual del agente y castea point
        space->getLocation(_id, ubicacion_agente);
        repast::Point<int> centro(ubicacion_agente);

        // Solicita los agentes adyacentes usando distancia de Von Neumann
        repast::VN2DGridQuery<Agente> VN2DQuery(space);
        VN2DQuery.query(centro, 1, false, agentes_adyacentes);

        // Recorre todos los agentes adyacentes corroborando si debe contagiarse o no
        for (auto agente : agentes_adyacentes ) {   
            
            if ( _prob_ser_contagiado > repast::Random::instance()->nextDouble() && agente->contagia() ) {
                _enfermo = true;
                std::cout << "FUI CONTAGIADO, ID " << _id << std::endl;
            }
            
        }
    }
}


void Agente::move(repast::SharedDiscreteSpace<Agente, repast::StrictBorders, repast::SimpleAdder<Agente> >* space, const Plano * plano){

    std::vector<int> agentLoc;
    space->getLocation(_id, agentLoc);
    
    std::vector<int> agentNewLoc;
    do {
        agentNewLoc.clear();
        double xRand = repast::Random::instance()->nextDouble();
        double yRand = repast::Random::instance()->nextDouble();
        agentNewLoc.push_back(agentLoc[0] + (xRand < .33 ? -1 : (xRand < .66 ? 0 : 1)));
        agentNewLoc.push_back(agentLoc[1] + (yRand < .33 ? -1 : (yRand < .66 ? 0 : 1)));
        // Note: checking to see if agent would move outside GLOBAL bounds; exceeding local bounds is OK
        if(!space->bounds().contains(agentNewLoc)) std::cout << " INVALID: " << agentNewLoc[0] << "," << agentNewLoc[1] << std::endl;
        
    } while( !space->bounds().contains(agentNewLoc) 
             || plano->hay_pared(agentNewLoc[0], agentNewLoc[1]) );
    
    space->moveTo(_id, agentNewLoc);
}

// Funciones para interaccion entre agentes

bool Agente::contagia() const {

    return ( _enfermo && _prob_contagiar > repast::Random::instance()->nextDouble() ) ? true : false;

}
