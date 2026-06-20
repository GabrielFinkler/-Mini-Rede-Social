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
            saida << "USER_ADDED\n";
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
        Usuario* seguidor = nullptr;
        Usuario* seguido = nullptr;
        
        if(buscar_arvore(rede.usuarios_por_id, id_seguidor, seguidor) && buscar_arvore(rede.usuarios_por_id, id_seguido, seguido)){
            bool ja_segue = contem(seguidor->usuarios_seguindo, [id_seguido](const Usuario& u) {
            
            return u.id_usuario == id_seguido; 
            });
            if((seguidor != seguido) && (!ja_segue)){
            seguirUsuario(rede, id_seguidor, id_seguido, saida);}else
            if(seguidor == seguido){
            saida << "ERROR CANNOT_FOLLOW_SELF\n";
            }else if(!ja_segue && seguidor == seguido){
            saida << "ERROR ALREADY_FOLLOWING\n";}
        
        }else
            saida << "ERROR USER_NOT_FOUND\n";

    }else if(funcao == "LIST_FOLLOWING"){
        int id_seguidor;
        entrada >> id_seguidor;
        Usuario* temp = nullptr;
        if (buscar_arvore(rede.usuarios_por_id, id_seguidor, temp)){
            listarSeguindo(rede, id_seguidor, saida);
        }else
            saida << "ERROR USER_NOT_FOUND";

    }else if(funcao == "ADD_POST"){
        int post_id;
        int author_id;
        int timestamp;
        string texto;
        Usuario* temp = nullptr;
        entrada >> post_id >> author_id >> timestamp >> texto; 
        if (buscar_arvore(rede.usuarios_por_id, author_id, temp)){
            bool ja_publi = contem(temp->publicacoes_postadas, [post_id](const Publicacao& u) {
            
            return u.id_publi == post_id; 
            });
            if(!ja_publi){
                cadastrarPublicacao(rede, post_id, author_id, timestamp, texto, saida)
            }else{
                saida << "ERROR POST_EXISTS";

            }
        }else{
            saida << "ERROR USER_NOT_FOUND";
        }

    }else if(funcao == "LIKE"){
        int id_autor;
        int id_post;
        Usuario* temp = nullptr;
        entrada >> id_autor >> id_post;
        if(buscar_arvore(rede.usuarios_por_id, id_autor, temp)){
            Publicacao* publi_encontrada = buscar_na_lista(temp->publicacoes_postadas, [id_post](const Publicacao& p) {
            return p.id_publi == id_post;
            });
            if(publi_encontrada != nullptr){
                bool ja_curtiu = contem(publi_encontrada->likers, [id_autor](const Publicacao& u) {
            
                return u.id_usuario == id_autor; 
                //if(!ja)
            });
                
            }else{
                saida << "ERROR POST_NOT_FOUND";
            }

        }else{
            saida << "ERROR USER_NOT_FOUND";
        }


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
     saida << "FOLLOWED\n";

     string notificacao = "NOTIFICATION FOLLOW " + seguidor->id_usuario;
     enqueue(seguido->notificacoes, notificacao);
}

void listarSeguindo(MiniRede& rede, int idUsuario, std::ostream& saida) {
    Usuario* seguidor = nullptr;
    buscar_arvore(rede.usuarios_por_id, idUsuario, seguidor);
    saida << "FOLLOWING_BEGIN\n";
    ordenar_lista(seguidor->usuarios_seguindo, [](const Usuario& a, const Usuario& b){
        return a.id_usuario < b.id_usuario;
    });
    imprimir_frente_usuario(seguidor->usuarios_seguindo,saida);
    saida << "FOLLOWING_END\n";
}

void cadastrarPublicacao(MiniRede& rede, int idPost, int idAutor, int timestamp, string texto, std::ostream& saida) {
    Usuario* autor = nullptr;
    Publicacao* publi;
    publi->id_publi = idPost;
    publi->id_usuario = idAutor;
    publi->timestamp = timestamp;
    publi->texto = texto;
    buscar_arvore(rede.usuarios_por_id, idAutor, autor);
    inserir_final(autor->publicacoes_postadas, *publi);
    saida << "POST_ADDED";
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

