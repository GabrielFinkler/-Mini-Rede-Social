#include "tabelaHash.hpp"

using namespace std;
// Inicializa a tabela alocando o vetor de baldes
void inicializar_hash(TabelaHashUsuarios &TH, int capacidade) {
    TH.capacidade = capacidade;
    TH.quantidade = 0;
    
    // Aloca o array de ponteiros
    TH.baldes = new NoHashUsuario*[capacidade];
    
    // Zera todos os ponteiros
    for (int i = 0; i < capacidade; i++) {
        TH.baldes[i] = nullptr;
    }
}

// =========================================================================
// FUNÇÃO HASH (Algoritmo djb2)
// =========================================================================
int calcular_indice_hash(string username, int capacidade) {
    unsigned long hash = 5381; // Valor inicial clássico do algoritmo djb2
    
    // Percorre cada letra do username
    for (int i = 0; i < username.length(); i++) {
        char letra = username[i];
        // Multiplica o hash atual por 33 e soma o valor ASCII da letra
        hash = (hash * 33) + letra; 
    }
    
    // Pega o resto da divisão para garantir que o número caiba no nosso vetor
    return hash % capacidade;
}
// =========================================================================

// Inserir ou atualizar na Hash
bool inserir_hash(TabelaHashUsuarios &TH, string username, Usuario* user) {
    if (TH.capacidade == 0) return false;

    int indice = calcular_indice_hash(username, TH.capacidade);
    NoHashUsuario* atual = TH.baldes[indice];

    // Passo 1: Verifica se a chave já existe. Se sim, apenas atualiza o ponteiro
    while (atual != nullptr) {
        if (atual->username == username) {
            atual->user = user;
            return true;
        }
        atual = atual->prox;
    }

    // Passo 2: Se não existe, cria um novo nó e insere no INÍCIO da lista daquele balde
    NoHashUsuario* novo = new NoHashUsuario(username, user);
    novo->prox = TH.baldes[indice];
    TH.baldes[indice] = novo;
    
    TH.quantidade++;
    return true;
}

// Buscar na Hash (Retorna true se achou, e joga o ponteiro na variável 'resultado')
bool buscar_hash(const TabelaHashUsuarios &TH, string username, Usuario* &resultado) {
    if (TH.capacidade == 0) return false;

    int indice = calcular_indice_hash(username, TH.capacidade);
    NoHashUsuario* atual = TH.baldes[indice];

    while (atual != nullptr) {
        if (atual->username == username) {
            resultado = atual->user; // Copia o ponteiro encontrado para a saída
            return true;
        }
        atual = atual->prox;
    }
    return false; // Usuário não encontrado
}

// Remover da Hash
bool remover_hash(TabelaHashUsuarios &TH, string username) {
    if (TH.capacidade == 0) return false;

    int indice = calcular_indice_hash(username, TH.capacidade);
    NoHashUsuario* atual = TH.baldes[indice];
    NoHashUsuario* anterior = nullptr;

    while (atual != nullptr) {
        if (atual->username == username) {
            if (anterior == nullptr) {
                // Era o primeiro elemento da lista daquele balde
                TH.baldes[indice] = atual->prox;
            } else {
                // Estava no meio ou fim da lista
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

// Liberar a memória da Hash
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