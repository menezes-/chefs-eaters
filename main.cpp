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


std::mutex mutex_cook;

std::condition_variable cv;

int qtde_comida_a_cozinhar{0};

bool no_food = false;

bool has_food = false;


void cozinheiro_thread(Travessa &travessa) {

    // espera até algum canibal notificar que não tem mais comida na travessa
    std::unique_lock<std::mutex> lk(mutex_cook);
    cv.wait(lk, [] { return no_food; });

    std::stringstream msg;
    msg << "Cozinheiro " << std::this_thread::get_id() << " Avisaram que não tem comida, fazendo " << qtde_comida_a_cozinhar << '\n';
    std::cout << msg.str();

    Cozinheiro::cook(travessa, qtde_comida_a_cozinhar);

    msg << "Cozinheiro " << std::this_thread::get_id() << " Quantidade de comida " << travessa.get_qtde_comida() << '\n';

    std::cout << msg.str();

    has_food = true;
    // solta o mutex
    lk.unlock();
    // avisa pros canibais que tem comida na travessa
    cv.notify_all();

}


void canibal_thread(Travessa &travessa, Mutex &mutex) {
    auto id = mutex.register_consumer();

    Randomer randomer{0, 100};

    // decide quanto eu quero comer
    auto quanto_quero_comer = randomer();
    std::stringstream msg;


    msg.clear();
    msg << "Canibal " << id << " qtde_de_comida " << travessa.get_qtde_comida() << " vou comer " << quanto_quero_comer << '\n';
    std::cout << msg.str();

    if (travessa.get_qtde_comida() < quanto_quero_comer) {


        qtde_comida_a_cozinhar += quanto_quero_comer;

        {
            std::lock_guard<std::mutex> lk(mutex_cook);
            no_food = true;
            msg.clear();
            msg << "Canibal " << id << " quer comer " << quanto_quero_comer << " mas não tem comida"
                << " Notificando cozinheiros" << '\n';
            std::cout << msg.str();

        }

        cv.notify_all();

        // avisa pra algum cozinheiro para de ser preguiçoso
        // espera a travessa ter a quantidade certa correta de comida
        {
            std::unique_lock<std::mutex> lk(mutex_cook);
            cv.wait(lk, [] { return has_food; });
            msg.clear();
            msg << "Canibal " << id << " cozinheiro diz que tem comida" << '\n';
            std::cout << msg.str();
        }

    }

    // usa nosso mutex para comer que nem um canibal comeria
    // /m/
    mutex.acquire(id);
    msg.clear();
    msg << "Canibal " << id << " comendo " << quanto_quero_comer << '\n'; // cu
    std::cout << msg.str();
    travessa.pop(quanto_quero_comer);

    if(travessa.get_qtde_comida() < 0){
        std::cout << "erro" << '\n';
    }

    mutex.release(id);


    msg.clear();
    msg << "Canibal " << id << " terminou de comer" << '\n'; // cu
    std::cout << msg.str();



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
    std::vector<std::thread> threads_cozinheiros;
    threads_cozinheiros.reserve(qtde_cozinheiros);
    threads_canibais.reserve(numero_de_canibais);

    for (int i = 0; i < qtde_cozinheiros; ++i) {
        threads_cozinheiros.emplace_back(cozinheiro_thread, std::ref(travessa));
    }

    for (int j = 0; j < numero_de_canibais; ++j) {
        // emplace back recebe os parâmetros passados para std::thread
        // e cria uma thread in place no vetor, não sendo necessaria uma alocação + cópia (alocar a thread e copiar para o vetor)
        threads_canibais.emplace_back(canibal_thread, std::ref(travessa), std::ref(mutex_proprio));
    }


    for (auto &thread: threads_canibais) {
        thread.join();
    }

    for (auto &thread: threads_cozinheiros) {
        thread.join();
    }

}
