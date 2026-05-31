#ifndef LISTA_DUPLAMENTE_H
#define LISTA_DUPLAMENTE_H

struct No;
struct Lista;

void inicializar(Lista &L);
bool vazia(const Lista &L);
bool eh_circular(const Lista &L);
void tornar_circular(Lista &L);
void desfazer_circular(Lista &L);
void inserir_inicio(Lista &L, int valor);
void inserir_final(Lista &L, int valor);
bool remover_valor(Lista &L, int valor);
void imprimir_frente(const Lista &L);
void imprimir_reverso(const Lista &L);
void imprimir_circular(Lista &L, int n);
void liberar_lista(Lista &L);

#endif
