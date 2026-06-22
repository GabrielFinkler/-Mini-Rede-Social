#ifndef ARVORE_BINARIA_H
#define ARVORE_BINARIA_H

#include <iostream>




struct Usuario;


struct NoArvore {
    int id;
    Usuario* user;   
    NoArvore* esq;   
    NoArvore* dir;   

    // Construtor
    NoArvore(int i, Usuario* u) : id(i), user(u), esq(nullptr), dir(nullptr) {}
};


struct ArvoreBinaria {
    NoArvore* raiz;
};

void inicializar_arvore(ArvoreBinaria &A);
bool inserir_arvore(ArvoreBinaria &A, int id, Usuario* user);
bool buscar_arvore(const ArvoreBinaria &A, int id, Usuario* &resultado);
void listar_crescente(const ArvoreBinaria &A, std::ostream& saida);
void liberar_arvore(ArvoreBinaria &A);

#endif // ARVORE_BINARIA_H