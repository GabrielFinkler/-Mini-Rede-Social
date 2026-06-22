#include "arvoreBinaria.hpp"
#include "../base.hpp"

using namespace std;

NoArvore* inserir_recursivo(NoArvore* atual, int id, Usuario* user, bool &inseriu) {
    if (atual == nullptr) {
        inseriu = true;
        return new NoArvore(id, user);
    }

    if (id < atual->id) {
        atual->esq = inserir_recursivo(atual->esq, id, user, inseriu);
    } 
    else if (id > atual->id) {
        atual->dir = inserir_recursivo(atual->dir, id, user, inseriu);
    } 
    else {
        inseriu = false;
    }

    return atual;
}

// impressão Em Ordem
void listar_recursivo(NoArvore* atual, std::ostream& saida) {
    if (atual != nullptr) {
        listar_recursivo(atual->esq, saida); 
        
        saida << "USER " << atual->id << " " << atual->user->username << " " << atual->user->nome_completo << endl;
        
        listar_recursivo(atual->dir, saida); 
    }
}


void liberar_recursivo(NoArvore* atual) {
    if (atual != nullptr) {
        liberar_recursivo(atual->esq); 
        liberar_recursivo(atual->dir); 
        delete atual;                  
    }
}



void inicializar_arvore(ArvoreBinaria &A) {
    A.raiz = nullptr;
}

bool inserir_arvore(ArvoreBinaria &A, int id, Usuario* user) {
    bool inseriu = false;
    A.raiz = inserir_recursivo(A.raiz, id, user, inseriu);
    return inseriu;
}

bool buscar_arvore(const ArvoreBinaria &A, int id, Usuario* &resultado) {
    NoArvore* atual = A.raiz;

    while (atual != nullptr) {
        if (atual->id == id) {
            resultado = atual->user; // Achou! Copia o ponteiro para o resultado
            return true;
        } else if (id < atual->id) {
            atual = atual->esq; // Procura na esquerda
        } else {
            atual = atual->dir; // Procura na direita
        }
    }
    return false; // Não achou
}

void listar_crescente(const ArvoreBinaria &A, std::ostream& saida) {
    if (A.raiz == nullptr) {
        return;
    }
    listar_recursivo(A.raiz, saida);
}

void liberar_arvore(ArvoreBinaria &A) {
    liberar_recursivo(A.raiz);
    A.raiz = nullptr;
}