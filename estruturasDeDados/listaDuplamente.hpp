#include <iostream>

using namespace std;


template <typename T>
struct Lista {
    No<T>* inicio; 
    No<T>* fim;

    // Construtor da lista 
    Lista() : inicio(nullptr), fim(nullptr) {}
};

template <typename T>
void inicializar(Lista<T> &L) {
    L.inicio = nullptr;
    L.fim = nullptr;
}

template <typename T>
bool vazia(const Lista<T> &L) {
    return L.inicio == nullptr;
}

template <typename T>
bool eh_circular(const Lista<T> &L) {
    if (vazia(L)) 
        return false;
    if(L.fim->prox == L.inicio && L.inicio->ant == L.fim ){
        return true;
    }
    return false;
}

template <typename T>
void tornar_circular(Lista<T> &L) {
    if (vazia(L)) 
        return;
    L.fim->prox = L.inicio;
    L.inicio->ant = L.fim;
}

template <typename T>
void desfazer_circular(Lista<T> &L) {
    if (!eh_circular(L)) return;
    L.inicio->ant = nullptr;
    L.fim->prox = nullptr;
}

template <typename T>
void inserir_inicio(Lista<T> &L, T valor) {
    No<T>* novo = new No<T>(valor); 
    
    if(L.inicio == nullptr){
        L.inicio = novo;
        L.fim = novo;
    }else{
        novo->prox = L.inicio;
        L.inicio->ant = novo;
        L.inicio = novo;
    }
}

template <typename T>
void inserir_final(Lista<T> &L, T valor) {
    No<T>* novo = new No<T>(valor);
    
    if(L.inicio == nullptr){
        L.inicio = novo;
        L.fim = novo;
    }else{
        novo->ant = L.fim;
        L.fim->prox = novo;
        L.fim = novo;
    }
}

template <typename T>
bool remover_valor(Lista<T> &L, T valor) {
    if(L.inicio == nullptr){
        return false;
    }
    No<T>* atual = L.inicio;
    while(atual != nullptr){
        if(atual->valor == valor){
            if(atual->prox == nullptr){
                if(atual == L.inicio){
                    //remove primeiro nó caso ele seja o único
                    delete atual;
                    L.inicio = nullptr;
                    L.fim = nullptr; 
                    return true;
                }else{
                    // remove ultimo nó
                    atual->ant->prox = nullptr;
                    L.fim = atual->ant; Atualizar o ponteiro fim da lista
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

template <typename T>
void imprimir_frente(const Lista<T> &L) {
    if (vazia(L)) {
        cout << "[ ]\n";
        return;
    }

    if (eh_circular(L)) {
        cout << "A lista e circular. Use imprimir_circular.\n";
        return;
    }

    No<T>* atual = L.inicio;
    cout << "[ ";
    while (atual != nullptr) {
        cout << atual->valor << " ";
        atual = atual->prox;
    }
    cout << "]\n";
}

template <typename T>
void imprimir_reverso(const Lista<T> &L) {
    if (vazia(L)) {
        cout << "[ ]\n";
        return;
    }

    if (eh_circular(L)) {
        cout << "A lista e circular. Use imprimir_circular.\n";
        return;
    }

    No<T>* atual = L.fim;
    cout << "[ ";
    while (atual != nullptr) {
        cout << atual->valor << " ";
        atual = atual->ant;
    }
    cout << "]\n";
}

template <typename T>
void imprimir_circular(Lista<T> &L, int n) {
    if (vazia(L)) {
        cout << "[ ]\n";
        return;
    }
    
    No<T>* atual = L.inicio;
    cout << "[ ";
    for (int i = 0; i < n; i++) {
        cout << atual->valor << " ";
        atual = atual->prox;
    }
    cout << "]\n";
}

template <typename T>
void liberar_lista(Lista<T> &L) {
    if (vazia(L)) return;

    if (eh_circular(L)) {
        desfazer_circular(L);
    }

    No<T>* atual = L.inicio;
    while (atual != nullptr) {
        No<T>* temp = atual;
        atual = atual->prox;
        delete temp;
    }

    L.inicio = nullptr;
    L.fim = nullptr;
}
