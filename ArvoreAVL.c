#include "ArvoreAVL.h"

#include <stdio.h>
#include <stdlib.h>

struct NO {
    int info;
    int alt;
    struct NO *esq;
    struct NO *dir;
};