#include "Cozinheiro.hpp"
#include <chrono>
#include <thread>




void Cozinheiro::cook(Travessa &travessa, int n) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    travessa.set_qtde_comida(travessa.get_qtde_comida() + n);
}
