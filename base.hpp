#ifndef MINI_REDE_H
#define MINI_REDE_H

#include <string>
#include "listaDuplamente.hpp"
#include "fila.hpp"
#include "tabelahash.hpp"
#include "arvoreBinaria.hpp"

using namespace std;

const int TAM_USERNAME = 50;
const int TAM_NOME = 100;
const int TAM_TEXTO = 280;
const int TAM_COMANDO = 30;

// TODO: definir as structs principais do trabalho.
//
// Sugestao de structs que provavelmente serao necessarias:
// - Usuario
// - Publicacao
// - MiniRede
// - nos para lista encadeada
// - nos para arvore binaria de usuarios por id
// - nos para tabela hash de usernames
// - nos para fila de notificacoes
//
// Os campos de cada struct fazem parte do projeto dos alunos.
template <typename T>
struct No {
    T valor;         
    No*  prox;  
    No*  ant;

    // Construtor 
    No(T value) : valor(value), prox(nullptr), ant(nullptr) {}
};




struct MiniRede {
    ArvoreBinaria usuarios_por_id;
    TabelaHashUsuarios usuarios_por_username;
    Lista<Publicacao> publicacoes; 

};

struct Usuario{
    int id_usuario;
    string username;
    string nome_completo;
    Lista<Usuario> usuarios_seguindo;
    Lista<Publicacao> publicacoes_postadas;
    Fila<string> notificacoes;

};

struct Publicacao{
    int id_publi;
    int id_usuario;
    int timestamp;
    string texto;
    int likes;
    Lista<Usuario> likers;
};



void inicializarMiniRede(MiniRede& rede);
void liberarMiniRede(MiniRede& rede);
void processarComandos(MiniRede& rede, std::istream& entrada, std::ostream& saida);

void cadastrarUsuario(MiniRede& rede, int id, const char username[], const char nomeCompleto[], std::ostream& saida);
void buscarUsuarioPorId(MiniRede& rede, int id, std::ostream& saida);
void buscarUsuarioPorUsername(MiniRede& rede, const char username[], std::ostream& saida);
void listarUsuarios(MiniRede& rede, std::ostream& saida);

void seguirUsuario(MiniRede& rede, int idSeguidor, int idSeguido, std::ostream& saida);
void listarSeguindo(MiniRede& rede, int idUsuario, std::ostream& saida);

void cadastrarPublicacao(MiniRede& rede, int idPost, int idAutor, int timestamp, const char texto[], std::ostream& saida);
void curtirPublicacao(MiniRede& rede, int idUsuario, int idPost, std::ostream& saida);

void consultarNotificacoes(MiniRede& rede, int idUsuario, int k, std::ostream& saida);
void gerarFeed(MiniRede& rede, int idUsuario, int k, std::ostream& saida);
void listarTopPosts(MiniRede& rede, int k, std::ostream& saida);

// TODO: declarar aqui as funcoes auxiliares escolhidas pelo grupo.
//
// Exemplos de responsabilidades auxiliares:
// - buscar usuario por id
// - buscar usuario por username
// - buscar publicacao por id
// - inserir/listar/liberar arvore
// - inserir/buscar/liberar tabela hash
// - enfileirar/desenfileirar notificacoes
// - manipular listas encadeadas
// - ordenar vetores auxiliares para feed e ranking


#endif
