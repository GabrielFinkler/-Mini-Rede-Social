#include "base.hpp"
#include <iostream>

using namespace std;

void inicializarMiniRede(MiniRede& rede) {
    inicializar_hash(rede.usuarios_por_username, 1009);
    inicializar_arvore(rede.usuarios_por_id);
    inicializar_lista(rede.publicacoes);
}

void liberarMiniRede(MiniRede& rede) {
    liberar_arvore(rede.usuarios_por_id);
    liberar_hash(rede.usuarios_por_username);
    liberar_lista(rede.publicacoes);
}

void processarComandos(MiniRede& rede, std::istream& entrada, std::ostream& saida) {
    string funcao;
    while (entrada >> funcao) {
    if (funcao == "ADD_USER"){
        int id;
        string username;
        string nome_completo;
        entrada >> id >> username >> nome_completo;

        saida << id << username << nome_completo;

    }else if(funcao == "FIND_USER"){
        // TODO
    }else if(funcao == "FIND_USERNAME"){
        // TODO
    }else if(funcao == "LIST_USERS"){
        // TODO
    }else if(funcao == "FOLLOW"){
        // TODO
    }else if(funcao == "LIST_FOLLOWING"){
        // TODO
    }else if(funcao == "ADD_POST"){
        // TODO
    }else if(funcao == "LIKE"){
        // TODO
    }else if(funcao == "GET_NOTIFICATIONS"){
        // TODO
    }else if(funcao == "FEED"){
        // TODO
    }else{
        saida << "entrada invalida" << endl;
    }
    } // fim do while
}
void cadastrarUsuario(MiniRede& rede, int id, const string& username, const string& nomeCompleto, std::ostream& saida) {
// Cria o usuário de verdade na memória Heap
    Usuario* novoUser = new Usuario;
    novoUser->id_usuario = id;
    novoUser->username = username;
    novoUser->nome_completo = nomeCompleto;

    // Salva na Árvore para busca por ID e listagem
    inserir_arvore(rede.usuarios_por_id, novoUser->id_usuario, novoUser);

    // Salva na Hash para busca por nome
    inserir_hash(rede.usuarios_por_username, novoUser->username, novoUser);

    saida << "Usuario cadastrado com sucesso!\n";
}
void buscarUsuarioPorId(MiniRede& rede, int id, std::ostream& saida) {
    // TODO
}

void buscarUsuarioPorUsername(MiniRede& rede, const char username[], std::ostream& saida) {
    // TODO
}

void listarUsuarios(MiniRede& rede, std::ostream& saida) {
    // TODO
}

void seguirUsuario(MiniRede& rede, int idSeguidor, int idSeguido, std::ostream& saida) {
    // TODO
}

void listarSeguindo(MiniRede& rede, int idUsuario, std::ostream& saida) {
    // TODO
}

void cadastrarPublicacao(MiniRede& rede, int idPost, int idAutor, int timestamp, const char texto[], std::ostream& saida) {
    // TODO
}

void curtirPublicacao(MiniRede& rede, int idUsuario, int idPost, std::ostream& saida) {
    // TODO
}

void consultarNotificacoes(MiniRede& rede, int idUsuario, int k, std::ostream& saida) {
    // TODO
}

void gerarFeed(MiniRede& rede, int idUsuario, int k, std::ostream& saida) {
    // TODO
}

void listarTopPosts(MiniRede& rede, int k, std::ostream& saida) {
    // TODO
}

int main() {
    MiniRede rede;

    inicializarMiniRede(rede);
    processarComandos(rede, std::cin, std::cout);
    liberarMiniRede(rede);

    return 0;
}

