#include "populacao.hpp"

#include <stdlib.h>

#include <iostream>

// Inicializa a mutacao da populacao
int Populacao::mutacao = TAXA_MUTACAO;

// Construtor da populacao
Populacao::Populacao() {
  this->index_melhor = 0;
  this->num_genocidios = 0;
  this->individuos = new Individuo[TAM_POPULACAO];
}

Populacao::~Populacao() {}

// Funcao de avaliacao da populacao
// Objetivo: buscar sempre o menor fitness e o menor numero de elementos no conjunto
void Populacao::avalia_populacao(int* conjunto) {
  int menor_fitness = this->individuos[this->index_melhor].fitness;
  int index_ultimo_melhor = this->index_melhor;

  // Percorre a populacao em busca do melhor individuo
  for (int i = 0; i < TAM_POPULACAO; i++) {
    this->individuos[i].calcula_fitness(conjunto);

    // Se encontrou um com menor fitness...
    if (menor_fitness > this->individuos[i].fitness) {
      menor_fitness = this->individuos[i].fitness;
      this->index_melhor = i;
    } else {  // Fitness nao eh melhor (ou seja, eh maior ou igual)
      // Se o fitness for igual, verifica se o numero de elementos eh menor para buscar o menor conjunto
      if (menor_fitness == this->individuos[i].fitness) {
        if (this->individuos[this->index_melhor].num_elementos > this->individuos[i].num_elementos) {
          this->index_melhor = i;
        }
      }
    }
  }

  // Se o index do melhor se manteve, incrementa o numero de repeticoes
  if (index_melhor == index_ultimo_melhor) {
    this->repeticoes++;
  } else {  // Se o melhor mudou, zera as repeticoes e os genocidios, alem de setar a mutacao para default
    this->repeticoes = 0;
    this->num_genocidios = 0;
    Populacao::mudanca_mutacao(TAXA_MUTACAO);
  }
}

// Realiza o elitismo, a mutacao e o genocidio, apos um alto numero de repeticoes
void Populacao::elitismo(void) {
  // cout << "Repeticoes: " << this->repeticoes << endl;

  // Se repetiu o mesmo fitness muitas vezes, aumenta a mutacao ate 5 por cento
  if (this->repeticoes >= NUM_REPETICOES) {
    this->repeticoes = 0;
    if (Populacao::mutacao < 5) {
      Populacao::mudanca_mutacao(Populacao::mutacao + 1);
    } else {
      // Se a mutacao atingiu 5 por cento, realiza o genocidio, mantendo o melhor individuo
      Populacao::genocidio();
      Populacao::mudanca_mutacao(TAXA_MUTACAO);
    }
    // cout << "Nova mutacao: " << Populacao::mutacao << endl;
  }

  // Elitismo e mutacao
  for (int i = 0; i < TAM_POPULACAO; i++) {
    if (this->index_melhor != i) {
      for (int j = 0; j < TAM_CONJUNTO; j++) {
        this->individuos[i].cromossomo[j] = (rand() % 2) ? this->individuos[i].cromossomo[j] : this->individuos[index_melhor].cromossomo[j];
        this->individuos[i].cromossomo[j] = (rand() % 100 < Populacao::mutacao) ? !this->individuos[i].cromossomo[j] : this->individuos[i].cromossomo[j];
      }
    }
  }
}

// Atualiza mutacao
void Populacao::mudanca_mutacao(int nova_mutacao) {
  Populacao::mutacao = nova_mutacao;
}

// Funcao que realiza o genocidio
// Mantem o melhor individuo da populacao
void Populacao::genocidio(void) {
  Individuo ind_melhor;
  ind_melhor = this->individuos[index_melhor];
  delete[] this->individuos;
  this->individuos = new Individuo[TAM_POPULACAO];
  this->individuos[index_melhor] = ind_melhor;
  this->num_genocidios++;
  cout << "Genocidio realizado!" << endl;
}