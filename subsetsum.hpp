#include <iostream>
#include <stdlib.h>
#include <time.h>

#define SOMA_ALVO 5000
#define TAM_POPULACAO 5
#define TAM_CONJUNTO 200
#define MAX_NUM 100
#define TAXA_MUTACAO 1
#define ITER_MAX 5000
#define NUM_REPETICOES 1000

using namespace std;

int* conjunto = new int[TAM_CONJUNTO];

void inicia_conjunto(int* conjunto, int size) {
  for(int i=0; i<size; i++) {
    conjunto[i] = (rand() % (MAX_NUM*2 + 1)) - MAX_NUM;
  }
}

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

    void calcula_fitness(void);
    Individuo();
    ~Individuo();
};

class Populacao
{
  private:
    int repeticoes = 0;

  public:
    Individuo * individuos;
    int index_melhor;
    static int mutacao;

    static void mudanca_mutacao(int nova_mutacao);
    void avalia_populacao(void);
    void elitismo(void);
    void genocidio(void);

    

    Populacao();
    ~Populacao();
};

int Populacao::mutacao = TAXA_MUTACAO;
 



