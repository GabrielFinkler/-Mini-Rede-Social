#ifndef FILA_H
#define FILA_H

#include <iostream>
#include "listaDuplamente.hpp" 
#include "base.hpp"


using namespace std;

// 1. Definição da Struct Fila como Template
template <typename T>
struct Fila {
    No<T>* inicio;
    No<T>* fim;

    // Construtor 
    Fila() : inicio(nullptr), fim(nullptr) {}
};


template <typename T>
void inicializar_fila(Fila<T> &F) {
    F.inicio = nullptr;
    F.fim = nullptr;
}

template <typename T>
bool fila_vazia(const Fila<T> &F) {
    return F.inicio == nullptr;
}

template <typename T>
bool fila_cheia(const Fila<T> &F) {
    return false;
}

template <typename T>
bool enqueue(Fila<T> &F, T valor) {
    // Usando o construtor do No que criamos anteriormente
    No<T>* atual = new No<T>(valor);
    
    if(fila_vazia(F)){
        F.inicio = atual;
        F.fim = atual;
        return true;
    }
    
    F.fim->prox = atual;
    F.fim = atual;
    return true;
}

template <typename T>
bool dequeue(Fila<T> &F) {
    if(fila_vazia(F)){
        return false;
    }
    
    No<T>* temp = F.inicio;
    
    if(F.inicio == F.fim){
        F.inicio = nullptr;
        F.fim = nullptr;
    } else {
        F.inicio = F.inicio->prox;
    }
    
    delete temp; 
    return true;
}


template <typename T>
T front(const Fila<T> &F) {
    return F.inicio->valor;
}

template <typename T>
void imprimir_fila(const Fila<T> &F) {
    No<T>* atual = F.inicio;
    cout << "[ ";
    while(atual != nullptr){
        // ATENÇÃO: Veja o aviso importante sobre esta linha logo abaixo
        cout << atual->valor << " "; 
        atual = atual->prox;
    }
    cout << "]\n";
}

#endif // FILA_H