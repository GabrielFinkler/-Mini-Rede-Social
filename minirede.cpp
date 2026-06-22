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
            }else if(ja_segue && seguidor != seguido){
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
            saida << "ERROR USER_NOT_FOUND\n";

    }else if(funcao == "ADD_POST"){
        int post_id;
        int author_id;
        int timestamp;
        string texto;
        Usuario* temp = nullptr;
        entrada >> post_id >> author_id >> timestamp >> texto; 
        if (buscar_arvore(rede.usuarios_por_id, author_id, temp)){
            bool ja_publi = contem(rede.publicacoes, [post_id](const Publicacao& p) {
            
            return p.id_publi == post_id; 
            });
            if(!ja_publi){
                cadastrarPublicacao(rede, post_id, author_id, timestamp, texto, saida);
            }else{
                saida << "ERROR POST_EXISTS\n";

            }
        }else{
            saida << "ERROR USER_NOT_FOUND\n";
        }

    }else if(funcao == "LIKE"){
        int id_liker;
        int id_post;
        Usuario* temp = nullptr;
        entrada >> id_liker>> id_post;
        if(buscar_arvore(rede.usuarios_por_id, id_liker, temp)){
            Publicacao* publi_encontrada = buscar_na_lista(rede.publicacoes, [id_post](const Publicacao& p) {
            return p.id_publi == id_post;
            });
            
            if(publi_encontrada != nullptr){
                bool ja_curtiu = contem(publi_encontrada->likers, [id_liker](const Usuario& u) {
            
                return u.id_usuario == id_liker; 
                });
                if(!ja_curtiu){
                    curtirPublicacao(rede, id_liker, id_post, publi_encontrada, saida);
                }else{
                    saida << "ERROR ALREADY_LIKED\n";
                }
                
            }else{
                saida << "ERROR POST_NOT_FOUND\n";
            }

        }else{
            saida << "ERROR USER_NOT_FOUND\n";
        }


    }else if(funcao == "GET_NOTIFICATIONS"){
        int k;
        int id_usuario;
        entrada >> id_usuario >> k;
        Usuario* temp = nullptr;
        if(buscar_arvore(rede.usuarios_por_id, id_usuario, temp)){
            consultarNotificacoes(rede, id_usuario, k, saida);
        }else {
            saida << "ERROR USER_NOT_FOUND\n";
        }
    }else if(funcao == "FEED"){
        int id_usuario;
        int k;
        entrada >> id_usuario >> k;
        Usuario* temp = nullptr;
        if(buscar_arvore(rede.usuarios_por_id, id_usuario, temp)){
            gerarFeed(rede, id_usuario, k, saida);
        }else {
            saida << "ERROR USER_NOT_FOUND\n";
        }
    }else if(funcao == "TOP_POSTS"){
        int k;
        entrada >> k;
        listarTopPosts(rede, k, saida);

    }else if(funcao == "END"){
        break;
    }else
        saida << "ERROR INVALID_COMMAND";
    }
}
void cadastrarUsuario(MiniRede& rede, int id, const string& username, const string& nomeCompleto, std::ostream& saida) {
    Usuario* novoUser = new Usuario;
    novoUser->id_usuario = id;
    novoUser->username = username;
    novoUser->nome_completo = nomeCompleto;

    inicializar_lista(novoUser->usuarios_seguindo);
    inicializar_lista(novoUser->publicacoes_postadas);
    inicializar_fila(novoUser->notificacoes);

    inserir_arvore(rede.usuarios_por_id, novoUser->id_usuario, novoUser);

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

     string notificacao = "NOTIFICATION FOLLOW " + to_string(seguidor->id_usuario) + "\n";
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
    Publicacao publi;
    publi.id_publi = idPost;
    publi.id_usuario = idAutor;
    publi.timestamp = timestamp;
    publi.texto = texto;
    publi.likes = 0;
    inicializar_lista(publi.likers);
    buscar_arvore(rede.usuarios_por_id, idAutor, autor);
    inserir_final(autor->publicacoes_postadas, publi);
    inserir_final(rede.publicacoes, publi);
    saida << "POST_ADDED\n";
}

void curtirPublicacao(MiniRede& rede, int idUsuario, int idPost, Publicacao* publi_encontrada, std::ostream& saida) {
    Usuario* temp = nullptr;
    buscar_arvore(rede.usuarios_por_id, idUsuario, temp);
    publi_encontrada->likes++;
    inserir_final(publi_encontrada->likers, *temp);
    string notificacao = "NOTIFICATION LIKE " + to_string(idUsuario) + " " + to_string(idPost) + "\n";
    Usuario* autor_do_post = nullptr;
    buscar_arvore(rede.usuarios_por_id, publi_encontrada->id_usuario, autor_do_post);
    enqueue(autor_do_post->notificacoes, notificacao);
    saida << "LIKED\n";
}

void consultarNotificacoes(MiniRede& rede, int idUsuario, int k, std::ostream& saida) {
    Usuario* temp = nullptr;
    buscar_arvore(rede.usuarios_por_id, idUsuario, temp);
    saida << "NOTIFICATIONS_BEGIN\n";
    print_notificacoes(temp->notificacoes, k, saida);
    saida << "NOTIFICATIONS_END\n";
}

void gerarFeed(MiniRede& rede, int idUsuario, int k, std::ostream& saida) {
    int impressos = 0;
    Lista<Publicacao> temp_feed;
    inicializar_lista(temp_feed);
    Usuario* temp = nullptr;
    buscar_arvore(rede.usuarios_por_id, idUsuario, temp);
    No<Publicacao>* atual_publi = rede.publicacoes.inicio;
    while(atual_publi != nullptr){
        bool segue_autor = contem(temp->usuarios_seguindo, [atual_publi](const Usuario& u) {
            return u.id_usuario == atual_publi->valor.id_usuario;
        });
        if(segue_autor){
            inserir_final(temp_feed, atual_publi->valor);
        }
        atual_publi = atual_publi->prox;
    }
    ordenar_lista(temp_feed, [](const Publicacao& a, const Publicacao& b) {
        if (a.timestamp != b.timestamp) {
            return a.timestamp > b.timestamp; 
        }
        return a.id_publi < b.id_publi;
    });
    saida << "FEED_BEGIN\n";
    imprimir_frente_publicacoes(temp_feed, k, saida);
    saida << "FEED_END\n";

}

void listarTopPosts(MiniRede& rede, int k, std::ostream& saida) {
    Lista<Publicacao> top_rank;
    inicializar_lista(top_rank);
    top_rank = rede.publicacoes;
    ordenar_lista(top_rank, [](const Publicacao& a, const Publicacao& b) {
        if (a.likes != b.likes) {
            return a.likes > b.likes; 
        }
        return a.id_publi < b.id_publi;
    });
    saida << "TOP_POSTS_BEGIN\n"; 
    imprimir_frente_publicacoes(top_rank, k,saida);
    saida << "TOP_POSTS_END\n";

}

int main() {
    MiniRede rede;

    inicializarMiniRede(rede);
    processarComandos(rede, std::cin, std::cout);
    liberarMiniRede(rede);

    return 0;
}

