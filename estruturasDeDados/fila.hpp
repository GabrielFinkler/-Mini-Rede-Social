#ifndef FILA_H
#define FILA_H

#include "listaDuplamente.hpp"
#include <iostream>

using namespace std;

template <typename T> struct Fila {
  No<T> *inicio;
  No<T> *fim;

  // Construtor
  Fila() : inicio(nullptr), fim(nullptr) {}
};

template <typename T> void inicializar_fila(Fila<T> &F) {
  F.inicio = nullptr;
  F.fim = nullptr;
}

template <typename T> bool fila_vazia(const Fila<T> &F) {
  return F.inicio == nullptr;
}

template <typename T> bool fila_cheia(const Fila<T> &F) { return false; }

template <typename T> bool enqueue(Fila<T> &F, T valor) {
  No<T> *atual = new No<T>(valor);

  if (fila_vazia(F)) {
    F.inicio = atual;
    F.fim = atual;
    return true;
  }

  F.fim->prox = atual;
  F.fim = atual;
  return true;
}

template <typename T> bool dequeue(Fila<T> &F) {
  if (fila_vazia(F)) {
    return false;
  }

  No<T> *temp = F.inicio;

  if (F.inicio == F.fim) {
    F.inicio = nullptr;
    F.fim = nullptr;
  } else {
    F.inicio = F.inicio->prox;
  }

  delete temp;
  return true;
}

template <typename T> T front(const Fila<T> &F) { return F.inicio->valor; }

template <typename T> 
void print_notificacoes(Fila<T> &F, int k, std::ostream& saida) {
    int contador = 0;

    while (!fila_vazia(F) && contador < k) {

        saida << front(F); 

        dequeue(F); 
        
        contador++;
    }
}

#endif // FILA_H