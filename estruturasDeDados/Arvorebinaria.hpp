#ifndef ARVORE_BINARIA_H
#define ARVORE_BINARIA_H

#include <iostream>

using namespace std;

// Declaração antecipada
struct Usuario;

// Nó da Árvore
struct NoArvore {
    int id;
    Usuario* user;   // Ponteiro para o usuário real
    NoArvore* esq;   // Filho da esquerda (IDs menores)
    NoArvore* dir;   // Filho da direita (IDs maiores)

    // Construtor
    NoArvore(int i, Usuario* u) : id(i), user(u), esq(nullptr), dir(nullptr) {}
};

// Estrutura principal da Árvore
struct ArvoreBinaria {
    NoArvore* raiz;
};

// ==========================================
// PROTOTIPAÇÃO DAS FUNÇÕES
// ==========================================
void inicializar_arvore(ArvoreBinaria &A);
bool inserir_arvore(ArvoreBinaria &A, int id, Usuario* user);
bool buscar_arvore(const ArvoreBinaria &A, int id, Usuario* &resultado);
void listar_crescente(const ArvoreBinaria &A, std::ostream& saida);
void liberar_arvore(ArvoreBinaria &A);

#endif // ARVORE_BINARIA_H