#ifndef POPULACAO_HPP_
#define POPULACAO_HPP_

#include "individuo.hpp"

#define TAXA_MUTACAO 1
#define TAM_POPULACAO 5
#define NUM_REPETICOES 1000

using namespace std;

class Populacao {
 private:
  int repeticoes = 0;

 public:
  Individuo* individuos;
  int index_melhor;
  static int mutacao;

  static void mudanca_mutacao(int nova_mutacao);
  void avalia_populacao(int* conjunto);
  void elitismo(void);
  void genocidio(void);

  Populacao();
  ~Populacao();
};

#endif  // POPULACAO_HPP_