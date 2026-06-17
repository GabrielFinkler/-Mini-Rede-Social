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
        Usuario* temp = nullptr;
        if (buscar_arvore(rede.usuarios_por_id, id, temp)){
            saida << "ERROR USER_EXISTS\n";
        }else{
            cadastrarUsuario(rede, id, username, nome_completo, saida);
        }
    }else if(funcao == "FIND_USER"){
        int id;
        entrada >> id;
        buscarUsuarioPorId(rede, id, saida);
    }else if(funcao == "FIND_USERNAME"){
        string username;
        entrada >> username;
        buscarUsuarioPorUsername(rede, username, saida);
    }else if(funcao == "LIST_USERS"){
        listarUsuarios(rede, saida);
    }else if(funcao == "FOLLOW"){
        int id_seguidor;
        int id_seguido;
        entrada >> id_seguidor >> id_seguido; 
        Usuario* temp = nullptr;
        if(buscar_arvore(rede.usuarios_por_id, id_seguidor, temp) && buscar_arvore(rede.usuarios_por_id, id_seguido, temp)){
           seguirUsuario(rede, id_seguidor, id_seguido, saida);
        }else
            saida << "ERROR USER_NOT_FOUND\n";

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

    inicializar_lista(novoUser->usuarios_seguindo);
    inicializar_lista(novoUser->publicacoes_postadas);
    inicializar_fila(novoUser->notificacoes);

    // Salva na Árvore para busca por ID e listagem
    inserir_arvore(rede.usuarios_por_id, novoUser->id_usuario, novoUser);

    // Salva na Hash para busca por nome
    inserir_hash(rede.usuarios_por_username, novoUser->username, novoUser);

    
}
void buscarUsuarioPorId(MiniRede& rede, int id, std::ostream& saida) {
    Usuario* temp = nullptr;
 
    if(buscar_arvore(rede.usuarios_por_id, id, temp)){
        saida << "USER " << temp->id_usuario << " " << temp->username << " " << temp->nome_completo << endl;
    }else
        saida << "ERROR USER_NOT_FOUND\n";

}

void buscarUsuarioPorUsername(MiniRede& rede, const string& username, std::ostream& saida) {
    Usuario* temp = nullptr;

    if(buscar_hash(rede.usuarios_por_username, username, temp)){
        saida << "USER " << temp->id_usuario << " " << temp->username << " " << temp->nome_completo << endl;
    }else
        saida << "ERROR USER_NOT_FOUND\n";
}

void listarUsuarios(MiniRede& rede, std::ostream& saida) {
    saida << "USERS_BEGIN\n";
    listar_crescente(rede.usuarios_por_id, saida);
    saida << "USERS_END\n";
}

void seguirUsuario(MiniRede& rede, int id_seguidor, int id_seguido, std::ostream& saida) {
     Usuario* seguidor = nullptr;
     Usuario* seguido = nullptr;
     buscar_arvore(rede.usuarios_por_id, id_seguidor, seguidor);
     buscar_arvore(rede.usuarios_por_id, id_seguido, seguido);
     
     inserir_final(seguidor->usuarios_seguindo, *seguido);

     string notificacao = "NOTIFICATION FOLLOW " + seguidor->id_usuario;
     enqueue(seguido->notificacoes, notificacao);
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

