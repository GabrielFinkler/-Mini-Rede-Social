#include "tabelaHash.hpp"

using namespace std;
void inicializar_hash(TabelaHashUsuarios &TH, int capacidade) {
    TH.capacidade = capacidade;
    TH.quantidade = 0;
    
    TH.baldes = new NoHashUsuario*[capacidade];
    
    for (int i = 0; i < capacidade; i++) {
        TH.baldes[i] = nullptr;
    }
}


int calcular_indice_hash(string username, int capacidade) {
    unsigned long hash = 5381; 
    
    
    for (int i = 0; i < username.length(); i++) {
        char letra = username[i];
        hash = (hash * 33) + letra; 
    }
    

    return hash % capacidade;
}



bool inserir_hash(TabelaHashUsuarios &TH, string username, Usuario* user) {
    if (TH.capacidade == 0) return false;

    int indice = calcular_indice_hash(username, TH.capacidade);
    NoHashUsuario* atual = TH.baldes[indice];

    
    while (atual != nullptr) {
        if (atual->username == username) {
            atual->user = user;
            return true;
        }
        atual = atual->prox;
    }

    
    NoHashUsuario* novo = new NoHashUsuario(username, user);
    novo->prox = TH.baldes[indice];
    TH.baldes[indice] = novo;
    
    TH.quantidade++;
    return true;
}

bool buscar_hash(const TabelaHashUsuarios &TH, string username, Usuario* &resultado) {
    if (TH.capacidade == 0) return false;

    int indice = calcular_indice_hash(username, TH.capacidade);
    NoHashUsuario* atual = TH.baldes[indice];

    while (atual != nullptr) {
        if (atual->username == username) {
            resultado = atual->user; 
            return true;
        }
        atual = atual->prox;
    }
    return false; 
}


bool remover_hash(TabelaHashUsuarios &TH, string username) {
    if (TH.capacidade == 0) return false;

    int indice = calcular_indice_hash(username, TH.capacidade);
    NoHashUsuario* atual = TH.baldes[indice];
    NoHashUsuario* anterior = nullptr;

    while (atual != nullptr) {
        if (atual->username == username) {
            if (anterior == nullptr) {
               
                TH.baldes[indice] = atual->prox;
            } else {
                
                anterior->prox = atual->prox;
            }
            delete atual; 
            TH.quantidade--;
            return true;
        }
        anterior = atual;
        atual = atual->prox;
    }
    return false;
}

void liberar_hash(TabelaHashUsuarios &TH) {
    if (TH.baldes == nullptr) return;

    for (int i = 0; i < TH.capacidade; i++) {
        NoHashUsuario* atual = TH.baldes[i];
        while (atual != nullptr) {
            NoHashUsuario* temp = atual;
            atual = atual->prox;
            delete temp;
        }
    }
    
    delete[] TH.baldes;
    TH.baldes = nullptr;
    TH.capacidade = 0;
    TH.quantidade = 0;
}