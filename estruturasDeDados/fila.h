#ifndef FILA_H
#define FILA_H

struct No;
struct Fila;

void inicializar_fila(Fila &F);
bool fila_vazia(const Fila &F);
bool fila_cheia(const Fila &F);
bool enqueue(Fila &F, int valor);
bool dequeue(Fila &F);
int front(const Fila &F);
void imprimir_fila(const Fila &F);

#endif
