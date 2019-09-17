
#include "Travessa.hpp"


int Travessa::get_qtde_comida() const {
    return comida;
}


int Travessa::pop(int n ) {
    if (comida - n <= 0) {
        return 0;
    }

    comida -= n;

    return comida;
}


Travessa::Travessa(int comida): comida(comida) {}


void Travessa::set_qtde_comida(int _comida) {
    comida = _comida;
}

