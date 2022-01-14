#ifndef INDIVIDUO_HPP_
#define INDIVIDUO_HPP_

#include "subsetsum.hpp"

// Classe que representa o individuo
class Individuo {
 private:
  void inicializa_individuo(int size);

 public:
  int fitness;                        // Fitness do individuo
  int num_elementos;                  // Numero de elementos do individuo
  bool* cromossomo;                   // Vetor que indica se o numero daquela posicao do conjunto faz parte do individuo

  // Sobrecarga do = para copiar um individuo
  Individuo operator=(const Individuo& ind) {
    this->fitness = ind.fitness;
    for (int i = 0; i < TAM_CONJUNTO; i++) {
      this->cromossomo[i] = ind.cromossomo[i];
    }
    return *this;
  }

  void calcula_fitness(int* conjunto);
  Individuo();
  ~Individuo();
};

#endif  // INDIVIDUO_HPP_