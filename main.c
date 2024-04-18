#include <stdio.h>

#include "ArvoreAVL.h"

int main(void) {
    ArvAVL *arv = cria_ArvAVL();
    // 1, 5, 2, 7, 3, 6, 8, 4, 9, 10
    insere_ArvAVL(arv, 1);
    insere_ArvAVL(arv, 1);
    insere_ArvAVL(arv, 5);
    insere_ArvAVL(arv, 2);
    insere_ArvAVL(arv, 7);
    insere_ArvAVL(arv, 3);
    insere_ArvAVL(arv, 6);
    insere_ArvAVL(arv, 8);
    insere_ArvAVL(arv, 4);
    insere_ArvAVL(arv, 9);
    insere_ArvAVL(arv, 10);

    // pre ordem
    pre_ordem(arv);
    printf("\n");

    // in ordem
    in_ordem(arv);
    printf("\n");

    // pos ordem
    pos_ordem(arv);
    printf("\n");

    libera_ArvAVL(arv);
    return 0;
}