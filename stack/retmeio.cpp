/**
 * @author      : Guilherme Wachs Lopes (gwachs@fei.edu.br)
 * @file        : imprimeMeio
 * @created     : quarta set 30, 2020 18:37:51 -03
 */
#include <iostream>
using namespace std;

struct Lista {
  Lista* prox;
  int v;
};


Lista* criaLista (int n) {
  Lista* inicio = nullptr;
  Lista* ultimo = nullptr;
  for (int i = 0; i < n; ++i) {
    Lista* novo = new Lista;
    novo->v = i;
    novo->prox = nullptr;
    if (!inicio)
      inicio = novo;

    if (ultimo)
      ultimo->prox = novo;

    ultimo = novo;
  }
  return inicio;
}

void destroiLista (Lista* inicio) {
  Lista* temp;
  while (inicio) {
    temp = inicio->prox;
    delete inicio;
    inicio = temp;
  }
}

Lista* retornaMeio (Lista* l) {
	int i = 0;
	Lista* newLista = new Lista;
	newLista = l;
	while(newLista){
		newLista = newLista->prox;
		i++;
	}
	if(i % 2 != 0)
		i = i/2 + 1;
	else
		i = i/2;
	int j = 1;
	newLista = l;
	while(j != i){
		newLista = newLista->prox;
		j++;
	}
	return newLista;


  
}

int main (int argc, char* argv[]) {
  for (int i = 3; i < 20; i += 3) {
    Lista* x = criaLista (i);
    Lista* m = retornaMeio (x);
    cout << m->v << endl;
    destroiLista (x);
  }
  return 0;
}

