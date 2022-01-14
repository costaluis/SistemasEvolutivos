#ifndef POPULACAO_HPP_
#define POPULACAO_HPP_

#include "individuo.hpp"

#define TAXA_MUTACAO 1              // Taxa de mutacao inicial
#define TAM_POPULACAO 10            // Numero de individuos da populacao
#define NUM_REPETICOES 1000         // Numero de repeticoes sequencias para aumentar a mutacao em 1 por cento

using namespace std;

// Classe que representa a populacao, ou seja, o conjunto de individuos
class Populacao {
 private:
  int repeticoes = 0;               // Numero de repeticoes sequenciais de um mesmo individuo melhor

 public:
  Individuo* individuos;            // Conjunto de individuos
  int index_melhor;                 // Index do melhor individuo da populacao
  int num_genocidios;               // Numero de genocidios sequenciais
  static int mutacao;               // Taxa de mutacao

  static void mudanca_mutacao(int nova_mutacao);
  void avalia_populacao(int* conjunto);
  void elitismo(void);
  void genocidio(void);

  Populacao();
  ~Populacao();
};

#endif  // POPULACAO_HPP_