#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

#include "subsetsum.hpp"
#include "individuo.hpp"
#include "populacao.hpp"

void inicia_conjunto(int* conjunto, int size) {
  for (int i = 0; i < size; i++) {
    conjunto[i] = (rand() % (MAX_NUM * 2 + 1)) - MAX_NUM;
  }
}

int main() {
  srand(time(NULL));
  Populacao pop;
  ofstream output_file;
  int* conjunto = new int[TAM_CONJUNTO];
  int num, ultimo_index = -1;

  inicia_conjunto(conjunto, TAM_CONJUNTO);
  output_file.open("../files/" OUTPUT_FILE);
  output_file << "Iteracao,Fitness,Num_elementos" << endl;

  int soma_pos = 0;

  for (int i = 0; i < TAM_CONJUNTO; i++) {
    if (conjunto[i] > 0) {
      soma_pos += conjunto[i];
    }
  }

  cout << "Soma alvo: " << SOMA_ALVO << endl;

  for (int i = 0;; i++) {
    pop.avalia_populacao(conjunto);
    pop.elitismo();

    if (ultimo_index != pop.index_melhor) {
      cout << endl
          << "Iteracao: " << i << endl;
      cout << "Melhor index: " << pop.index_melhor << endl;
      cout << "Soma positivos: " << soma_pos << endl;
      cout << "Melhor fitness: " << pop.individuos[pop.index_melhor].fitness << endl;

      num = 0;
      for (int i = 0; i < TAM_CONJUNTO; i++) {
        if (pop.individuos[pop.index_melhor].cromossomo[i]) {
          num++;
        }
      }

      cout << "Numeros usados: " << num << endl;
      ultimo_index = pop.index_melhor;

      output_file << i << "," << pop.individuos[pop.index_melhor].fitness << "," << num << endl;
    }
    if (pop.num_genocidios > MAX_GENOCIDIOS) {
      break;
    }
  }

  for (int i=0; i<TAM_CONJUNTO; i++) {
    if (pop.individuos[pop.index_melhor].cromossomo[i]) {
      cout << "(" << conjunto[i] << ")" << " + ";
    }
  }
  cout << endl;
  cout << "Numeros usados: " << num << endl;
  cout << "Melhor fitness: " << pop.individuos[pop.index_melhor].fitness << endl;
  output_file.close();
}
