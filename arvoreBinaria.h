#ifndef ARVOREBINARIA_H_INCLUDED
#define ARVOREBINARIA_H_INCLUDED
#define true 1
#define false 0

typedef int bool;
typedef int TipoChave;

typedef struct aux {
    TipoChave chave;
    //dados aqui
    struct aux *esq, *dir;
    int h; //guarda a altura de cada n�
} NO;

typedef NO* Pont;


#endif // ARVOREBINARIA_H_INCLUDED
