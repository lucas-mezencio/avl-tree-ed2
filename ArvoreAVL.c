#include "ArvoreAVL.h"

#include <stdio.h>
#include <stdlib.h>

int alt_NO(struct NO *no);
int fator_balanceamento_NO(struct NO *no);
int maior(int x, int y);
void libera_NO(struct NO *no);

struct NO {
    int info;
    int alt;
    struct NO *esq;
    struct NO *dir;
};

ArvAVL *cria_ArvAVL() {
    ArvAVL *raiz = (ArvAVL *)malloc(sizeof(ArvAVL));
    if (raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_ArvAVL(ArvAVL *raiz) {
    if (raiz == NULL)
        return;
    libera_NO(*raiz);
    free(raiz);
}

void libera_NO(struct NO *no) {
    if (no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

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

struct NO* procuraMenor(struct NO* atual){
    struct NO *no1 = atual;
    struct NO *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

int remove_ArvAVL(ArvAVL *raiz, int valor){
	if(*raiz == NULL){// valor n�o existe
	    printf("valor n�o existe!!\n");
	    return 0;
	}

    int res;
	if(valor < (*raiz)->info){
	    if((res = remove_ArvAVL(&(*raiz)->esq,valor)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir))
                    RotacaoRR(raiz);
                else
                    RotacaoRL(raiz);
            }
	    }
	}

	if((*raiz)->info < valor){
	    if((res = remove_ArvAVL(&(*raiz)->dir, valor)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq) )
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
	    }
	}

	if((*raiz)->info == valor){
	    if(((*raiz)->esq == NULL || (*raiz)->dir == NULL)){// n� tem 1 filho ou nenhum
			struct NO *oldNode = (*raiz);
			if((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
			free(oldNode);
		}else { // n� tem 2 filhos
			struct NO* temp = procuraMenor((*raiz)->dir);
			(*raiz)->info = temp->info;
			remove_ArvAVL(&(*raiz)->dir, (*raiz)->info);
            if(fatorBalanceamento_NO(*raiz) >= 2){
				if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
					RotacaoLL(raiz);
				else
					RotacaoLR(raiz);
			}
		}
		if (*raiz != NULL)
            (*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;
		return 1;
	}

	(*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;

	return res;
}

void RotacaoLL(ArvAVL *A) {
    struct NO *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->alt = maior(alt_NO((*A)->esq), alt_NO((*A)->dir) + 1);
    B->alt = maior(alt_NO(B->esq), (*A)->alt + 1);
    *A = B;
}

void RotacaoRR(ArvAVL *A) {
    struct NO *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->alt = maior(alt_NO((*A)->esq), alt_NO((*A)->dir) + 1);
    B->alt = maior(alt_NO(B->dir), (*A)->alt + 1);
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

void pre_ordem(ArvAVL *A) {
    if (A == NULL)
        return;
    if (*A != NULL) {
        printf("%d ", (*A)->info);
        pre_ordem(&((*A)->esq));
        pre_ordem(&((*A)->dir));
    }
}

void in_ordem(ArvAVL *A) {
    if (A == NULL)
        return;
    if (*A != NULL) {
        in_ordem(&(*A)->esq);
        printf("%d ", (*A)->info);
        in_ordem(&(*A)->dir);
    }
}

void pos_ordem(ArvAVL *A) {
    if (A == NULL)
        return;
    if (*A != NULL) {
        pos_ordem(&(*A)->esq);
        pos_ordem(&(*A)->dir);
        printf("%d ", (*A)->info);
    }
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