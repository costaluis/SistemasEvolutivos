#include "subsetsum.hpp"

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

void Individuo::calcula_fitness(void)
{ 
  int soma = 0;
  for (int i=0; i<TAM_CONJUNTO; i++) {
    soma += (this->cromossomo[i]) ? conjunto[i] : 0;
  }

  this->fitness = abs(soma - SOMA_ALVO);
}

Populacao::Populacao()
{
  this->index_melhor = -1;
  this->individuos = new Individuo[TAM_POPULACAO];
}

Populacao::~Populacao(){}



void Populacao::avalia_populacao(void)
{
  int menor_fitness = __INT_MAX__;
  int index_ultimo_melhor = this->index_melhor;

  for (int i=0; i<TAM_POPULACAO; i++) {
    this->individuos[i].calcula_fitness();

    if (menor_fitness > this->individuos[i].fitness) {
      menor_fitness = this->individuos[i].fitness;
      this->index_melhor = i;
    }
  }

  if (index_melhor == index_ultimo_melhor) {
    this->repeticoes++;
  } else {
    this->repeticoes = 0;
    Populacao::mudanca_mutacao(TAXA_MUTACAO);
  }
}

void Populacao::elitismo(void)
{
  cout << "Repeticoes: " << this->repeticoes << endl;

  if(this->repeticoes >= NUM_REPETICOES) {
    this->repeticoes = 0;
    if (Populacao::mutacao < 5) {
      Populacao::mudanca_mutacao(Populacao::mutacao+1);
    }
    else {
      Populacao::genocidio();
      Populacao::mudanca_mutacao(TAXA_MUTACAO);
    }
    cout << "Nova mutacao: " << Populacao::mutacao << endl;
  }

  for (int i=0; i<TAM_POPULACAO; i++) {
    if (this->index_melhor != i) {
      for (int j=0; j<TAM_CONJUNTO; j++) {
        this->individuos[i].cromossomo[j] = (rand() % 2) ? this->individuos[i].cromossomo[j] : this->individuos[index_melhor].cromossomo[j];
        this->individuos[i].cromossomo[j] = (rand() % 100 < Populacao::mutacao) ? !this->individuos[i].cromossomo[j] : this->individuos[i].cromossomo[j];
      }
    }
  }
}

void Populacao::mudanca_mutacao(int nova_mutacao)
{
  Populacao::mutacao = nova_mutacao;
}

void Populacao::genocidio(void)
{
  Individuo ind_melhor;
  ind_melhor = this->individuos[index_melhor];
  delete[] this->individuos;
  this->individuos = new Individuo[TAM_POPULACAO];
  this->individuos[index_melhor] = ind_melhor;
}

int main()
{
  srand(time(NULL));
  Populacao pop;

  inicia_conjunto(conjunto, TAM_CONJUNTO);

  int soma_pos = 0;

  for (int i=0; i<TAM_CONJUNTO; i++) {
    if(conjunto[i] > 0) {
      soma_pos += conjunto[i];
    }
  }

  cout << "Soma alvo: " << SOMA_ALVO << endl;

  for (int i=0; ; i++) {
    pop.avalia_populacao();
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
