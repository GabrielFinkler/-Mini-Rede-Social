#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#include <string>



// Declaração antecipada para o compilador saber que 'Usuario' existe
struct Usuario;

// Nó específico para a Hash de Usuários
struct NoHashUsuario {
    std::string username; // A chave
    Usuario* user;   // O valor (ponteiro para o usuário real)
    NoHashUsuario* prox;

    // Construtor
    NoHashUsuario(std::string u, Usuario* us) : username(u), user(us), prox(nullptr) {}
};

// Estrutura da Tabela Hash específica
struct TabelaHashUsuarios {
    NoHashUsuario** baldes;
    int capacidade;
    int quantidade;
};

// Prototipação das funções
void inicializar_hash(TabelaHashUsuarios &TH, int capacidade);
int calcular_indice_hash(std::string username, int capacidade);
bool inserir_hash(TabelaHashUsuarios &TH, std::string username, Usuario* user);
bool buscar_hash(const TabelaHashUsuarios &TH, std::string username, Usuario* &resultado);
bool remover_hash(TabelaHashUsuarios &TH, std::string username);
void liberar_hash(TabelaHashUsuarios &TH);

#endif // TABELA_HASH_H