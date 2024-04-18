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
    // verifica se a arvore e vazia
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
    // verifica se o valor e menor que o valor da raiz
    if (valor < atual->info) {
        // se verdadeiro vai para subarvore da esquerda

        // chama recursivamente a funcao de insercao
        if ((res = insere_ArvAVL(&(atual->esq), valor)) == 1) {
            // testa o balanceamento
            if (fator_balanceamento_NO(atual) >= 2) {
                if (valor < (*raiz)->esq->info)
                    // se desbalanceado "reto" a esquerda
                    RotacaoLL(raiz);
                else
                    // se desbalanceado em "ziguezague" a esquerda e depois direita
                    RotacaoLR(raiz);
            }
        }
    } else {
        // se falso vai para subarvore da direita
        if (valor > atual->info) {
            // chama recursivamente a função de insercao
            if ((res = insere_ArvAVL(&(atual->dir), valor)) == 1) {
                // testa o balanceamento
                if (fator_balanceamento_NO(atual) >= 2) {
                    if ((*raiz)->dir->info < valor)
                        // se desbalanceado "reto" a direita
                        RotacaoRR(raiz);
                    else
                        // se desbalanceado em "ziguezague" a direita e depois esquerda
                        RotacaoRL(raiz);
                }
            }
        } else {
            // se ja existir sai da funcao
            printf("valor duplicado %d\n", valor);
            return 0;
        }
    }
    // recalcula a altura para o no atual
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