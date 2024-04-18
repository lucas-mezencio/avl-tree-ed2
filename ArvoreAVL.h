typedef struct NO* ArvAVL;

ArvAVL* cria_ArvAVL();
void libera_ArvAVL(ArvAVL* raiz);
int insere_ArvAVL(ArvAVL* raiz, int valor);
int remove_ArvAVL(ArvAVL* raiz, int valor);
int esta_vazia_ArvAVL(ArvAVL* raiz);
int altura_ArvAVL(ArvAVL* raiz);
int totalNO_ArvAVL(ArvAVL* raiz);
int consulta_ArvAVL(ArvAVL* raiz, int valor);

void pre_ordem(ArvAVL* A);
void in_ordem(ArvAVL* A);
void pos_ordem(ArvAVL* A);

void RotacaoLL(ArvAVL* A);
void RotacaoRR(ArvAVL* A);
void RotacaoLR(ArvAVL* A);
void RotacaoRL(ArvAVL* A);