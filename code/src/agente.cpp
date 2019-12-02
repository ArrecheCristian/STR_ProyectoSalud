/* Demo_03_Agent.cpp */

#include <iostream>

#include "agente.h"
#include "repast_hpc/Moore2DGridQuery.h"
#include "repast_hpc/VN2DGridQuery.h"
#include "repast_hpc/Point.h"

Agente::Agente(const repast::AgentId id, const float prob_contagio, const float prob_ser_contagiado, const bool enfermo) 
    :   _id{id},
        _prob_contagiar{prob_contagio},
        _prob_ser_contagiado{prob_ser_contagiado},
        _enfermo{enfermo} { }

Agente::~Agente() { }

void Agente::play(repast::SharedContext<Agente>* context,
                  repast::SharedDiscreteSpace<Agente, repast::StrictBorders, repast::SimpleAdder<Agente> >* space){

    // Trata de contagiar a sus adyacente solo si está enfermo
    if (_enfermo) {
        
        std::vector<Agente *> agentes_adyacentes;
        std::vector<int> ubicacion_agente;

        // Obtiene la ubicación actual del agente y castea point
        space->getLocation(_id, ubicacion_agente);
        repast::Point<int> centro(ubicacion_agente);

        // Solicita los agentes adyacentes usando distancia de Von Neumann
        repast::VN2DGridQuery<Agente> VN2DQuery(space);
        VN2DQuery.query(centro, 1, false, agentes_adyacentes);

        // Recorre todos los agentes adyacentes tratando de contagiarlos
        for (auto agente : agentes_adyacentes ) {
            if ( _prob_contagiar > repast::Random::instance()->nextDouble() ) agente->contagiar();

        }
    }
}


void Agente::move(repast::SharedDiscreteSpace<Agente, repast::StrictBorders, repast::SimpleAdder<Agente> >* space){

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
        
    } while(!space->bounds().contains(agentNewLoc));
    
    // TODO cambiar el while para que salga si no encuentra ninguna posición para moverse
    space->moveTo(_id,agentNewLoc);
}

// Funciones para interaccion entre agentes

void Agente::contagiar() {

    if ( !_enfermo && _prob_ser_contagiado > repast::Random::instance()->nextDouble() )  {
        _enfermo = true;
        std::cout << "FUI CONTAGIADO, ID " << _id << std::endl;
    }

}
