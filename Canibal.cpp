#include "Canibal.hpp"
#include "Cozinheiro.hpp"


Canibal::Canibal(Travessa &travessa)
    : travessa(travessa) {}


void Canibal::eat(int n) {
    if (travessa.get_qtde_comida() - n <= 0) {
        Cozinheiro::cook(travessa, n);
    }

    for (int i = 0; i < n; ++i) {
        travessa.pop();
    }
}
