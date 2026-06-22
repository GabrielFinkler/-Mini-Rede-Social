#ifndef MINI_REDE_H
#define MINI_REDE_H

#include <string>
#include "estruturasDeDados\listaDuplamente.hpp"
#include "estruturasDeDados\fila.hpp"
#include "estruturasDeDados\tabelahash.hpp"
#include "estruturasDeDados\arvoreBinaria.hpp"



const int TAM_USERNAME = 50;
const int TAM_NOME = 100;
const int TAM_TEXTO = 280;
const int TAM_COMANDO = 30;



struct Usuario;
struct Publicacao;

struct MiniRede {
    ArvoreBinaria usuarios_por_id;
    TabelaHashUsuarios usuarios_por_username;
    Lista<Publicacao> publicacoes; 

};

struct Usuario{
    int id_usuario;
    std::string username;
    std::string nome_completo;
    Lista<Usuario> usuarios_seguindo;
    Lista<Publicacao> publicacoes_postadas;
    Fila<std::string> notificacoes;

};

struct Publicacao{
    int id_publi;
    int id_usuario;
    int timestamp;
    std::string texto;
    int likes;
    Lista<Usuario> likers;
};



void inicializarMiniRede(MiniRede& rede);
void liberarMiniRede(MiniRede& rede);
void processarComandos(MiniRede& rede, std::istream& entrada, std::ostream& saida);

void cadastrarUsuario(MiniRede& rede, int id, const std::string& username, const std::string& nomeCompleto, std::ostream& saida);
void buscarUsuarioPorId(MiniRede& rede, int id, std::ostream& saida);
void buscarUsuarioPorUsername(MiniRede& rede, const string& username, std::ostream& saida);
void listarUsuarios(MiniRede& rede, std::ostream& saida);

void seguirUsuario(MiniRede& rede, int id_seguidor, int id_seguido, std::ostream& saida);
void listarSeguindo(MiniRede& rede, int idUsuario, std::ostream& saida);

void cadastrarPublicacao(MiniRede& rede, int idPost, int idAutor, int timestamp, string texto, std::ostream& saida);
void curtirPublicacao(MiniRede& rede, int idUsuario, int idPost, Publicacao* publi_encontrada, std::ostream& saida);

void consultarNotificacoes(MiniRede& rede, int idUsuario, int k, std::ostream& saida);
void gerarFeed(MiniRede& rede, int idUsuario, int k, std::ostream& saida);
void listarTopPosts(MiniRede& rede, int k, std::ostream& saida);




#endif
