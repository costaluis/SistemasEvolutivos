#include "populacao.hpp"

#include <stdlib.h>

#include <iostream>

int Populacao::mutacao = TAXA_MUTACAO;

Populacao::Populacao() {
  this->index_melhor = -1;
  this->individuos = new Individuo[TAM_POPULACAO];
}

Populacao::~Populacao() {}

void Populacao::avalia_populacao(int* conjunto) {
  int menor_fitness = __INT_MAX__;
  int index_ultimo_melhor = this->index_melhor;

  for (int i = 0; i < TAM_POPULACAO; i++) {
    this->individuos[i].calcula_fitness(conjunto);

    if (menor_fitness > this->individuos[i].fitness) {
      menor_fitness = this->individuos[i].fitness;
      this->index_melhor = i;
    } else {
      if (menor_fitness == this->individuos[i].fitness) {
        if (this->individuos[this->index_melhor].num_elementos > this->individuos[i].num_elementos) {
          this->index_melhor = i;
        }
      }
    }
  }

  if (index_melhor == index_ultimo_melhor) {
    this->repeticoes++;
  } else {
    this->repeticoes = 0;
    Populacao::mudanca_mutacao(TAXA_MUTACAO);
  }
}

void Populacao::elitismo(void) {
  cout << "Repeticoes: " << this->repeticoes << endl;

  if (this->repeticoes >= NUM_REPETICOES) {
    this->repeticoes = 0;
    if (Populacao::mutacao < 5) {
      Populacao::mudanca_mutacao(Populacao::mutacao + 1);
    } else {
      Populacao::genocidio();
      Populacao::mudanca_mutacao(TAXA_MUTACAO);
    }
    cout << "Nova mutacao: " << Populacao::mutacao << endl;
  }

  for (int i = 0; i < TAM_POPULACAO; i++) {
    if (this->index_melhor != i) {
      for (int j = 0; j < TAM_CONJUNTO; j++) {
        this->individuos[i].cromossomo[j] = (rand() % 2) ? this->individuos[i].cromossomo[j] : this->individuos[index_melhor].cromossomo[j];
        this->individuos[i].cromossomo[j] = (rand() % 100 < Populacao::mutacao) ? !this->individuos[i].cromossomo[j] : this->individuos[i].cromossomo[j];
      }
    }
  }
}

void Populacao::mudanca_mutacao(int nova_mutacao) {
  Populacao::mutacao = nova_mutacao;
}

void Populacao::genocidio(void) {
  Individuo ind_melhor;
  ind_melhor = this->individuos[index_melhor];
  delete[] this->individuos;
  this->individuos = new Individuo[TAM_POPULACAO];
  this->individuos[index_melhor] = ind_melhor;
  cout << "Genocidio realizado!" << endl;
}