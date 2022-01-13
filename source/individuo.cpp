#include "individuo.hpp"

#include <stdlib.h>

#include <iostream>

Individuo::Individuo() {
  this->cromossomo = new bool[TAM_CONJUNTO];
  this->inicializa_individuo(TAM_CONJUNTO);
}

Individuo::~Individuo() {
}

void Individuo::inicializa_individuo(int size) {
  for (int i = 0; i < size; i++) {
    this->cromossomo[i] = (rand() % 2);
  }
}

void Individuo::calcula_fitness(int* conjunto) {
  int soma = 0;
  int num_elementos = 0;

  for (int i = 0; i < TAM_CONJUNTO; i++) {
    if (this->cromossomo[i]) {
      soma += conjunto[i];
      num_elementos++;
    }
  }

  this->fitness = abs(soma - SOMA_ALVO);
  this->num_elementos = num_elementos;
}