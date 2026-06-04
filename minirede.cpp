#include "base.hpp"
#include <iostream>


void inicializarMiniRede(MiniRede& rede) {
    inicializar_hash(rede.usuarios_por_username, 1009);
}

void liberarMiniRede(MiniRede& rede) {
    // TODO
}

void processarComandos(MiniRede& rede, std::istream& entrada, std::ostream& saida) {
    // TODO: ler comandos da entrada padrao ate END.
    // Para cada comando, chamar a funcao correspondente.
    // Nao imprimir menu, prompt ou texto extra.
}

void cadastrarUsuario(MiniRede& rede, int id, const char username[], const char nomeCompleto[], std::ostream& saida) {
// Cria o usuário de verdade na memória Heap
    Usuario* novoUser = new Usuario;
    novoUser->id_usuario = id;
    novoUser->username = username;
    novoUser->nome_completo = nomeCompleto;
    // ... (inicializa as listas e filas de dentro dele) ...

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

