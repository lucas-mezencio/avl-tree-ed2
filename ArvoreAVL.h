typedef struct NO* ArvAVL;

ArvAVL* cria_ArvAVL();
void libera_ArvAVL(ArvAVL* raiz);
int insere_ArvAVL(ArvAVL* raiz, int valor);
int remove_ArvAVL(ArvAVL* raiz, int valor);
int esta_vazia_ArvAVL(ArvAVL* raiz);
int altura_ArvAVL(ArvAVL* raiz);
int totalNO_ArvAVL(ArvAVL* raiz);
int consulta_ArvAVL(ArvAVL* raiz, int valor);