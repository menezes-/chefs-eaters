#ifndef CANNIBALS_TRAVESSA_HPP
#define CANNIBALS_TRAVESSA_HPP
#include <atomic>

/**
 * Represanta uma travessa na qual os canibais pegam comida
 */
class Travessa {
public:

    explicit Travessa(int comida);

    int get_qtde_comida() const;

    void set_qtde_comida(int _comida);



    /**
     * retira uma unidade de comida da travessa
     * @return qtde - 1
     */
    int pop();

private:
    // quantidade de comida na travessa
    std::atomic_int comida;


};


#endif //CANNIBALS_TRAVESSA_HPP
