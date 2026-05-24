struct No{
    int valor;
    No* prox;
};

struct Fila {
    No* inicio;
    No* fim;
};

void inicializar_fila(Fila &F) {
    F.inicio = nullptr;
    F.fim = nullptr;
}

bool fila_vazia(const Fila &F) {
    if(F.inicio == nullptr)
        return true;
    return false;
}

bool fila_cheia(const Fila &F) {
    // Visto que a fila foi implementada utilizando uma lista encadeada ela não tem limite de itens.(A não ser quando acabar a memória)
    return false;
}

bool enqueue(Fila &F, int valor) {
    No* atual = new No();
    atual->valor = valor;
    atual->prox = nullptr;
    if(fila_vazia(F)){
        F.inicio = atual;
        F.fim = atual;
        return true;
    }
         F.fim->prox = atual;
         F.fim = atual;
    return true;
}

bool dequeue(Fila &F) {
    No* temp = F.inicio;
    if(fila_vazia(F)){
        return false;
    }if(F.inicio == F.fim){
        F.inicio = nullptr;
        F.fim = nullptr;
        delete temp;
        return true;
    }
        F.inicio = F.inicio->prox;
        delete temp; 
    return true;
}

int front(const Fila &F) {
        return F.inicio->valor;
}

void imprimir_fila(const Fila &F) {
    No* atual = F.inicio;
    cout << "[ ";
    while(atual != nullptr){
        cout << atual->valor << " ";
        atual = atual->prox;
    }
    cout << "]";
}
