#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <sstream>
#include "Travessa.hpp"
#include "Mutex.hpp"
#include "Cozinheiro.hpp"
#include "Randomer.hpp"


void canibal_thread(Travessa &travessa, Mutex &mutex) {
    auto id = mutex.register_consumer();

    Randomer randomer{1, 300};

    // decide quanto eu quero comer
    auto quanto_quero_comer = randomer();

    Randomer randomer1{1, quanto_quero_comer};

    std::stringstream msg;


    msg.clear();
    msg << "Canibal " << id << " qtde_de_comida " << travessa.get_qtde_comida() << " vou comer " << quanto_quero_comer
        << '\n';
    std::cout << msg.str();

    mutex.acquire(id);

    if (travessa.get_qtde_comida() < quanto_quero_comer) {

        int to_cook = quanto_quero_comer;

        msg.clear();
        msg << "Canibal " << id << " mandando cozinhar " << to_cook << '\n';
        std::cout << msg.str();
        Cozinheiro::cook(travessa, to_cook);

    }


    // usa nosso mutex para comer que nem um canibal comeria
    // /m/
    msg.clear();
    msg << "Canibal " << id << " comendo " << quanto_quero_comer << '\n'; // cu
    std::cout << msg.str();
    travessa.pop(quanto_quero_comer);
    mutex.release(id);

}


int main(int argc, char **argv) {
    std::vector<std::string> args(argv, argv + argc);

    int numero_de_canibais = std::stoi(args[1]);
    int qtde_de_comida = std::stoi(args[2]);
    int qtde_cozinheiros{1};
    if (args.size() == 4) {
        qtde_cozinheiros = std::stoi(args[3]);
    }

    Mutex mutex_proprio{numero_de_canibais};
    Travessa travessa{qtde_de_comida};

    std::vector<std::thread> threads_canibais;

    threads_canibais.reserve(numero_de_canibais);


    for (int j = 0; j < numero_de_canibais; ++j) {
        // emplace back recebe os parâmetros passados para std::thread
        // e cria uma thread in place no vetor, não sendo necessaria uma alocação + cópia (alocar a thread e copiar para o vetor)
        threads_canibais.emplace_back(canibal_thread, std::ref(travessa), std::ref(mutex_proprio));
    }


    for (auto &thread: threads_canibais) {
        thread.join();
    }



}
