#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#include <string>



struct Usuario;

struct NoHashUsuario {
    std::string username; 
    Usuario* user;   
    NoHashUsuario* prox;

    // Construtor
    NoHashUsuario(std::string u, Usuario* us) : username(u), user(us), prox(nullptr) {}
};

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