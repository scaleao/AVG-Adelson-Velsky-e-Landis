#include <stdio.h>
#include <stdlib.h>
#include "arvoreBinaria.h"

int main(){
    Pont r = inicializa();

    r = insere(r, 5);

    r = insere(r, 3);

    r = insere(r, 10);

    r = insere(r, 1);

    r = insere(r, 4);

    r = insere(r, 8);

    r = insere(r, 11);

    r = insere(r, 2);

    r = insere(r, 7);

    r = insere(r, 9);

    r = insere(r, 12);

    r = insere(r, 6);
    /*
    r = insere(r, 5);
    r = insere(r, 2);
    r = insere(r, 7);
    r = insere(r, 1);
    r = insere(r, 3);
    r = insere(r, 6);
    r = insere(r, 10);
    r = insere(r, 9);
    r = insere(r, 11);
    */

    //leituraPreOrdem(r);
    leitura(r, r->chave);
    printf("\n");

    r = remover(r, 5);
    leitura(r, r->chave);
    printf("\n");

    leitura(r, r->chave);
    return 0;
}
