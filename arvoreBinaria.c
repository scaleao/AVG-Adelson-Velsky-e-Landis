#include <stdio.h>
#include "arvoreBinaria.h"

Pont inicializa() {
    return(NULL);
}

Pont criaNovoNo(TipoChave ch) {
    Pont novoNo = (Pont)malloc(sizeof(NO));
    novoNo->chave = ch;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->h = 0;
    return(novoNo);
}

int max(int a, int b){
    if (a > b) return a;
    return b;
}

int altura(Pont raiz) {
    if (!raiz) return -1;
    return raiz->h;
}

int fatorB(Pont raiz) {
    return (altura(raiz->esq) - altura(raiz->dir));
}

// Rota��o � DIREITA - LL
Pont direita(Pont r) {
    Pont aux;
    aux = r->esq; //aux � a sub�rvore da esquerda do n� desbalanceado
    r->esq = aux->dir; //r adota o filho de aux
    aux->dir = r; //aux passa a ser pai de r

    //atualiza as alturas dos n�s que foram rotacionados
    r->h = max(altura(r->dir), altura(r->esq)) + 1;
    aux->h = max(altura(aux->esq), r->h) + 1;

    return(aux); //retorna a nova raiz
}

// Rota��o � ESQUERDA - RR
Pont esquerda(Pont r) {
    Pont aux;
    aux = r->dir; //aux � a sub�rvore da direita do n� desbalanceado
    r->dir = aux->esq; //r adota o filho de aux
    aux->esq = r; //aux passa a ser pai de r

    //atualiza as alturas dos n�s que foram rotacionados
    r->h = max(altura(r->dir), altura(r->esq)) + 1;
    aux->h = max(altura(aux->esq), r->h) + 1;

    return(aux); //retorna a nova raiz
}

Pont esquerdaDireita(Pont r) { //LR
    r->esq = esquerda(r->esq); //rotaciona o filho � esquerda do n� desbalanceado
    return(direita(r)); //rota��o � direita do n� desbalanceado
}

Pont direitaEsquerda(Pont r) {
    r->dir = direita(r->dir); //rotaciona o filho � direita do n� desbalanceado
    return(esquerda(r)); //rota��o � esquerda do n� desbalanceado
}

Pont rotacao(Pont raiz) {

    if (fatorB(raiz) >= 2){ // +2 = desbalanceamento � esquerda
        if (fatorB(raiz->esq) == 0 || fatorB(raiz->esq) == 1) // n� inserido � menor que o filho � esquerda do n� desbalanceado?
            raiz = direita(raiz);
        else
            raiz = esquerdaDireita(raiz);
    }
    if (fatorB(raiz) <= -2){ // -2 = desbalanceamento � direita
        if (fatorB(raiz->dir) == 0 || fatorB(raiz->dir) == -1) // n� inserido � maior que o filho � direita do n� desbalanceado?
            raiz = esquerda(raiz);
        else
            raiz = direitaEsquerda(raiz);
    }

    return raiz;
}

//fun��o INSER��O
Pont insere(Pont raiz, TipoChave ch) {
    if (!raiz) return(criaNovoNo(ch));

    /*a chamada recursiva de insere ir� percorrer a �rvore at� encontrar o
     o lugar onde o n� ser� inserido, ent�o, o mesmo � inserido com a chamada
     criaNo(ch) */

    if (ch < raiz->chave) {
        raiz->esq = insere(raiz->esq, ch);

        raiz = rotacao(raiz);
    }
    else{
        if (ch > raiz->chave){
            raiz->dir = insere(raiz->dir, ch);

            raiz = rotacao(raiz);
        }
        else {
            printf("Valor %d duplicado!!\n", ch);
        }
    }
    raiz->h = max(altura(raiz->esq), altura(raiz->dir)) + 1;
    return(raiz);
}

// Fun��es para REMO��O
Pont procuraNo(Pont q, Pont p){
    if (q->chave == p->chave){
        q->h = max(altura(q->esq), altura(q->dir)) + 1;
        q = rotacao(q);
        return q;
    }
    if (p->chave < q->chave){
        q = procuraNo(q->esq, p);
    }
    else{
        q = procuraNo(q->dir, p);
    }
    q->h = max(altura(q->esq), altura(q->dir)) + 1;
    q = rotacao(q);
    return q;
}

Pont remover(Pont raiz, TipoChave ch){
    if (!raiz){
        printf("Valor n�o encontrado! Arvore vazia!\n");
    }

    Pont pai = NULL; //vai ser o pai do n� removido

    if (ch < raiz->chave){
        pai = raiz->esq;
        raiz->esq = remover(raiz->esq, ch);
        //Remo��o foi feita � esquerda
        // Se a remo��o foi feita � esquerda, verifico se h� desbalanceamento � direita
        raiz = rotacao(raiz);
    }
    else if (ch > raiz->chave){
        pai = raiz->dir;
        raiz->dir = remover(raiz->dir, ch);
        // remo��o foi feita � direita
        // Se a remo��o foi feita � direita, verifico se h� desbalanceamento � esquerda
        raiz = rotacao(raiz);
    }
    else if (ch == raiz->chave){ //achei n� a ser removido
        Pont p = NULL, q;
        //p vai ser o pai do substituto
        //q vai marcar o n� substituto
        if (!raiz->esq || !raiz->dir){ //n� a ser removido tem 1 filho

            if(!raiz->esq)
                q = raiz->dir;
            else
                q = raiz->esq;

        }
        else{ //n� a ser removido tem 2 filhos
            // busca o n� a ser substitu�do
            // substituir pelo n� mais � direita da sub�rvore da esquerda
            p = raiz;
            q = raiz->esq;

            while(q->dir){
                p = q;
                q = q->dir;
            }

            if (p != raiz) { // o pai do n� substituto � o n� a ser removido?
                p->dir = q->esq;
                q->esq = raiz->esq;
            }
            q->dir = raiz->dir;

            if (p == raiz) //se q for igual o no removido, fa�o a rota��o somente em q
                q = rotacao(q);
            else if (p->chave < q->chave)
                q->esq = procuraNo(q, p);
            else q->dir = procuraNo(q, p);

            q->h = max(altura(q->esq), altura(q->dir)) + 1;
            q = rotacao(q);
        }
        if(!pai) { //n� a ser removido � o n� raiz?
            free(raiz);
            return(q);
        }

        if (ch < pai->chave)
            pai->esq = q;
        else
            pai->dir = q;

        free(raiz);

        q->h = max(altura(q->esq), altura(q->dir)) + 1;

        return q;
    }
    else
        printf("Chave n�o encontrada!!\n");

    raiz->h = max(altura(raiz->esq), altura(raiz->dir)) + 1;
    return raiz;
}

// Leitura PR� ORDEM - raiz, esq, dir
void leituraPreOrdem(Pont raiz){
    if (raiz != NULL) {
        printf("%d ", raiz->chave);
        leituraPreOrdem(raiz->esq);
        leituraPreOrdem(raiz->dir);
    }
}

/* Exibe arvore Pre-Ordem indicando pai de cada no    */
// chavePai recebe a chave da raiz
void leitura(Pont raiz, TipoChave chavePai){
	if (raiz != NULL){
	printf("(%i,%i) ",chavePai,raiz->chave);
	leitura(raiz->esq,raiz->chave);
	leitura(raiz->dir,raiz->chave);
	}
}
