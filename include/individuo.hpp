#ifndef INDIVIDUO_HPP_
#define INDIVIDUO_HPP_

#include "subsetsum.hpp"

#define SOMA_ALVO 5000

class Individuo
{
  private:
    void inicializa_individuo(int size);

  public:
    int fitness;
    bool* cromossomo;

    Individuo operator=(const Individuo &ind) {
      this->fitness = ind.fitness;
      for (int i=0; i<TAM_CONJUNTO; i++) {
        this->cromossomo[i] = ind.cromossomo[i];
      }
      return *this;
    }

    void calcula_fitness(int* conjunto);
    Individuo();
    ~Individuo();
};

#endif // INDIVIDUO_HPP_