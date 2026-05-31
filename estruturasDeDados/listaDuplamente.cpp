#include <iostream>
#include "base.h"
#include "listaDuplamente.h"
#include <iostream>

using namespace std;

void inicializar(Lista &L) {
    L.inicio = nullptr;
    L.fim = nullptr;
}

bool vazia(const Lista &L) {
    return L.inicio == nullptr;
}

bool eh_circular(const Lista &L) {
    if (vazia(L)) 
        return false;
    if(L.fim->prox == L.inicio && L.inicio->ant == L.fim ){
        return true;
    }
    return false;
}

void tornar_circular(Lista &L) {
    if (vazia(L)) 
        return;
    L.fim->prox = L.inicio;
    L.inicio->ant = L.fim;
}

void desfazer_circular(Lista &L) {
    if (!eh_circular(L)) return;
    L.inicio->ant = nullptr;
    L.fim->prox = nullptr;
}

void inserir_inicio(Lista &L, int valor) {
    No* novo = new No(); 
    novo->valor = valor;
    novo->ant = nullptr;
    novo->prox = nullptr;
    if(L.inicio == nullptr){
        L.inicio = novo;
        L.fim = novo;
    }else{
        novo->prox = L.inicio;
        L.inicio->ant = novo;
        L.inicio = novo;
    }

}

void inserir_final(Lista &L, int valor) {
    No* novo = new No();
    novo->valor = valor;
    novo->prox = nullptr; 
    if(L.inicio == nullptr){
        novo->ant = nullptr;
        L.inicio = novo;
        L.fim = novo;
    }else{
        novo->ant = L.fim;
        L.fim->prox = novo;
        L.fim = novo;
    }
}

bool remover_valor(Lista &L, int valor) {
    if(L.inicio == nullptr){
        //cout << "A lista está vazia";
        return false;
    }
    No* atual = L.inicio;
    while(atual != nullptr){
        if(atual->valor == valor){
            if(atual->prox == nullptr){
                if(atual == L.inicio){
                    //remove primeiro nó caso ele seja o único
                    delete atual;
                    L.inicio = nullptr;
                    return true;
                }else{
                    // remove ultimo nó
                    atual->ant->prox = nullptr;
                    delete atual;
                    return true;
                }
            }else{
                if(atual == L.inicio){
                    //remove o primeiro nó caso ele não seja o único
                    L.inicio = atual->prox;
                    atual->prox->ant = nullptr;
                    delete atual;
                    return true;
                }
                //nó do meio
                atual->ant->prox = atual->prox;
                atual->prox->ant = atual->ant;
                delete atual;
                return true;
            }
        }
        atual = atual->prox;

    } 
    return false;
}

void imprimir_frente(const Lista &L) {
    if (vazia(L)) {
        cout << "[ ]\n";
        return;
    }

    if (eh_circular(L)) {
        cout << "A lista e circular. Use imprimir_circular.\n";
        return;
    }

    No* atual = L.inicio;
    cout << "[ ";
    while (atual != nullptr) {
        cout << atual->valor << " ";
        atual = atual->prox;
    }
    cout << "]\n";
}

void imprimir_reverso(const Lista &L) {
    if (vazia(L)) {
        cout << "[ ]\n";
        return;
    }

    if (eh_circular(L)) {
        cout << "A lista e circular. Use imprimir_circular.\n";
        return;
    }

    No* atual = L.fim;
    cout << "[ ";
    while (atual != nullptr) {
        cout << atual->valor << " ";
        atual = atual->ant;
    }
    cout << "]\n";
}


void imprimir_circular(Lista &L, int n) {
    No* atual = L.inicio;
    cout << "[ ";
    for (int i =0;i < n; i++) {
        cout << atual->valor << " ";
        atual = atual->prox;
    }
    cout << "]\n";
}

void liberar_lista(Lista &L) {
    if (vazia(L)) return;

    if (eh_circular(L)) {
        desfazer_circular(L);
    }

    No* atual = L.inicio;
    while (atual != nullptr) {
        No* temp = atual;
        atual = atual->prox;
        delete temp;
    }

    L.inicio = nullptr;
    L.fim = nullptr;
}