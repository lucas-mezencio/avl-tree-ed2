#include "ArvoreAVL.h"

#include <stdio.h>
#include <stdlib.h>

struct NO {
    int info;
    int alt;
    struct NO *esq;
    struct NO *dir;
};

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