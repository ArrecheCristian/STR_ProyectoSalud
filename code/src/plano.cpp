#include "plano.h"

#include <vector>

plano::plano(const int ancho, const int alto, const std::vector<bool> paredes) : _ancho(ancho), _alto(alto), _plano(paredes) {
    
}

bool plano::hay_pared(const int x, const int y) const {
    return _plano[y * _ancho + x];
}
