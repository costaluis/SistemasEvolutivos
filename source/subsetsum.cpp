#include "subsetsum.hpp"
#include "individuo.hpp"
#include "populacao.hpp"

void inicia_conjunto(int* conjunto, int size) {
  for(int i=0; i<size; i++) {
    conjunto[i] = (rand() % (MAX_NUM*2 + 1)) - MAX_NUM;
  }
}

int main()
{
  srand(time(NULL));
  Populacao pop;
  int* conjunto = new int[TAM_CONJUNTO];

  inicia_conjunto(conjunto, TAM_CONJUNTO);

  int soma_pos = 0;

  for (int i=0; i<TAM_CONJUNTO; i++) {
    if(conjunto[i] > 0) {
      soma_pos += conjunto[i];
    }
  }

  cout << "Soma alvo: " << SOMA_ALVO << endl;

  for (int i=0; ; i++) {
    pop.avalia_populacao(conjunto);
    pop.elitismo();

    cout << endl << "Iteracao: " << i << endl;
    cout << "Melhor index: " << pop.index_melhor << endl;
    cout << "Soma positivos: " << soma_pos << endl;
    cout << "Melhor fitness: " << pop.individuos[pop.index_melhor].fitness << endl;
    
    if(pop.individuos[pop.index_melhor].fitness == 0) {
      break;
    }
  }

  int num = 0;
  for (int i=0; i<TAM_CONJUNTO; i++) {
    if (pop.individuos[pop.index_melhor].cromossomo[i]) {
      num++;
      cout << "(" << conjunto[i] << ")" << " + ";
    }
  }
  
  cout << endl;
  cout << "Numeros usados: " << num << endl;

}
