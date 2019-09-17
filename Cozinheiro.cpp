#include "Cozinheiro.hpp"
#include <chrono>
#include <thread>

#ifndef MILLISECONDS_TO_COOK_SINGLE_MEAL
#define MILLISECONDS_TO_COOK_SINGLE_MEAL 1000
#endif


void Cozinheiro::cook(Travessa &travessa, int n) {
    std::this_thread::sleep_for(std::chrono::milliseconds(n * MILLISECONDS_TO_COOK_SINGLE_MEAL));
    travessa.set_qtde_comida(n);
}
