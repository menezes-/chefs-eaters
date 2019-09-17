
#include "Travessa.hpp"


int Travessa::get_qtde_comida() const {
    return comida;
}


int Travessa::pop() {
    if (comida <= 0) {
        return 0;
    }
    return --comida;
}


Travessa::Travessa(int comida): comida(comida) {}


void Travessa::set_qtde_comida(int _comida) {
    comida = _comida;
}

