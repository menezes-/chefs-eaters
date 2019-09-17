#include "Mutex.hpp"
#include <thread>
#include <chrono>


int Mutex::register_consumer() {
    auto c = curr_consumer++;
    consumers[c] = false;
    return c;
}


void Mutex::acquire(int id) {
    // indica que quer entrar na seção critica
    consumers[id] = true;

    // da um chance pra outra thread adquirir a lock

    turn = id - 1;

    while (consumers[id - 1] && turn == id - 1) {
        // spinlock/busy wainting é coisa de amador... Não acredito que isso ainda é sugerido em certas
        // fontes educacionais
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }

}


void Mutex::release(int id) {
    consumers[id] = false;
}


Mutex::Mutex(int nconsumers): consumers(nconsumers, false) {

}
