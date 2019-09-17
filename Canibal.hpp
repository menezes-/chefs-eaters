
#ifndef CANNIBALS_CANIBAL_HPP
#define CANNIBALS_CANIBAL_HPP


#include "Travessa.hpp"
class Canibal {
public:
    explicit Canibal(Travessa &travessa);

    void eat(int n = 1);

private:
    Travessa &travessa;

};


#endif //CANNIBALS_CANIBAL_HPP
