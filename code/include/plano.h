#ifndef PLANO_H
#define PLANO_H

#include <vector>

class plano {

    private:
        const int _ancho;
        const int _alto;
        
        const std::vector<bool> _plano;

    public:

    /**
     * Crea un plano que detalla la ubicación de las paredes
     * 
     * @param ancho Ancho del mapa
     * @param alto Alto del mapa
     * @param paredes Vector de tamaño ancho*alto que contiene true donde haya paredes.
     */
    plano(const int ancho, const int alto, std::vector<bool> paredes);

    /**
     * Pregunta si hay pared en una coordenada dada
     * 
     * @param x coordenada en X
     * @param y coordenada en Y
     * @return True si hay una pared, false caso contrario
     */
    bool hay_pared(const int x, const int y) const;
};

#endif
