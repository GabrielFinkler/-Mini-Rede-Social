#include "arvoreBinaria.hpp"
#include "base.hpp"


//inserir usando recursão
NoArvore* inserir_recursivo(NoArvore* atual, int id, Usuario* user, bool &inseriu) {
    // Se achou um espaço vazio, cria o nó aqui!
    if (atual == nullptr) {
        inseriu = true;
        return new NoArvore(id, user);
    }

    // Se o ID for menor, vai para a esquerda
    if (id < atual->id) {
        atual->esq = inserir_recursivo(atual->esq, id, user, inseriu);
    } 
    // Se o ID for maior, vai para a direita
    else if (id > atual->id) {
        atual->dir = inserir_recursivo(atual->dir, id, user, inseriu);
    } 
    // Se for igual, não insere (ID duplicado!)
    else {
        inseriu = false;
    }

    return atual;
}

// impressão Em Ordem (In-Order: Esq -> Raiz -> Dir)
void listar_recursivo(NoArvore* atual, std::ostream& saida) {
    if (atual != nullptr) {
        listar_recursivo(atual->esq, saida); // 1. Vai tudo para a esquerda (menores)
        
        // 2. Imprime o nó atual (Raiz)
        saida << "ID: " << atual->id << " | Username: @" << atual->user->username << "\n";
        
        listar_recursivo(atual->dir, saida); // 3. Vai para a direita (maiores)
    }
}

//deletar a árvore (Pós-Ordem: Esq -> Dir -> Raiz)
void liberar_recursivo(NoArvore* atual) {
    if (atual != nullptr) {
        liberar_recursivo(atual->esq); // Deleta os filhos da esquerda primeiro
        liberar_recursivo(atual->dir); // Deleta os filhos da direita
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
        saida << "Nenhum usuario cadastrado.\n";
        return;
    }
    listar_recursivo(A.raiz, saida);
}

void liberar_arvore(ArvoreBinaria &A) {
    liberar_recursivo(A.raiz);
    A.raiz = nullptr;
}