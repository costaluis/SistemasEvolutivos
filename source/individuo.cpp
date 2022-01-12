#include <iostream>
#include <stdlib.h>

#include "individuo.hpp"

Individuo::Individuo()
{
  this->cromossomo = new bool[TAM_CONJUNTO];
  this->inicializa_individuo(TAM_CONJUNTO);
}

Individuo::~Individuo()
{
  // delete[] this->cromossomo;
}

void Individuo::inicializa_individuo(int size)
{
  for (int i=0; i<size; i++) {
    this->cromossomo[i] = (rand() % 2);
  }
}

void Individuo::calcula_fitness(int* conjunto)
{ 
  int soma = 0;
  for (int i=0; i<TAM_CONJUNTO; i++) {
    soma += (this->cromossomo[i]) ? conjunto[i] : 0;
  }

  this->fitness = abs(soma - SOMA_ALVO);
}