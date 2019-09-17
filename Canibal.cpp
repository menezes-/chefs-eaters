#include "Canibal.hpp"


Canibal::Canibal(Travessa &travessa)
    : travessa(travessa) {}


void Canibal::eat(int n) {

    for (int i = 0; i < n; ++i) {
        travessa.pop();
    }
}
