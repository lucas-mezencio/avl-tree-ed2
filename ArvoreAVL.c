#include "ArvoreAVL.h"

#include <stdio.h>
#include <stdlib.h>

struct NO {
    int info;
    int alt;
    struct NO *esq;
    struct NO *dir;
};

int insere_ArvAVL(ArvAVL *raiz, int valor) {
    int res;
    if (*raiz == NULL) {
        struct NO *novo = (struct NO *)malloc(sizeof(struct NO));
        if (novo == NULL)
            return 0;

        novo->info = valor;
        novo->alt = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
    if (valor < atual->info) {
        if ((res = insere_ArvAVL(&(atual->esq), valor)) == 1) {
            if (fator_balanceamento_NO(atual) >= 2) {
                if (valor < (*raiz)->esq->info)
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
        }
    } else {
        if (valor > atual->info) {
            if ((res = insere_ArvAVL(&(atual->dir), valor)) == 1) {
                if (fator_balanceamento_NO(atual) >= 2) {
                    if ((*raiz)->dir->info < valor)
                        RotacaoRR(raiz);
                    else
                        RotacaoRL(raiz);
                }
            }
        } else {
            printf("valor duplicado %d\n", valor);
            return 0;
        }
    }
    atual->alt = maior(alt_NO(atual->esq), alt_NO(atual->dir)) + 1;
    return res;
}
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