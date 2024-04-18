#include "ArvoreAVL.h"

#include <stdio.h>
#include <stdlib.h>

struct NO {
    int info;
    int alt;
    struct NO *esq;
    struct NO *dir;
};

void RotacaoLL(ArvAVL *A) {
    struct NO *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->alt = maior(alt_NO((*A)->esq), alt_NO((*A)->dir) + 1);
    B->alt = maior(alt_NO(B->esq), alt_NO((*A)->alt) + 1);
    *A = B;
}

void RotacaoRR(ArvAVL *A) {
    struct NO *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->alt = maior(alt_NO((*A)->esq), alt_NO((*A)->dir) + 1);
    B->alt = maior(alt_NO(B->dir), alt_NO((*A)->alt) + 1);
    (*A) = B;
}

void RotacaoLR(ArvAVL *A) {
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

void RotacaoRL(ArvAVL *A) {
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}

int alt_NO(struct NO *no) {
    if (no == NULL)
        return -1;
    return no->alt;
}

int fator_balanceamento_NO(struct NO *no) {
    return labs(alt_NO(no->esq) - alt_NO(no->dir));
}

int maior(int x, int y) {
    if (x > y) {
        return x;
    }
    return y;
}