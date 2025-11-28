#ifndef CIFRA_H
#define CIFRA_H

#define TAMANHO_ALFABETO 26

typedef struct {
    char mapeamento[TAMANHO_ALFABETO];
    int descoberto[TAMANHO_ALFABETO]; // 1 se a letra foi descoberta, 0 caso contrário
} Chave;

// Inicializa a chave vazia
void inicializarChave(Chave *chave);

// Criptografa um texto usando cifra de deslocamento
void criptografarDeslocamento(const char *textoClaro, char *textoCifrado, int deslocamento);

// Decifra um texto usando a chave atual
void decifrarTexto(const char *textoCifrado, char *textoDecifrado, const Chave *chave);

// Adiciona um mapeamento à chave
void adicionarMapeamento(Chave *chave, char original, char cifrado);

// Exibe a chave atual
void exibirChave(const Chave *chave);

// Salva a chave em um arquivo
void salvarChave(const Chave *chave, const char *nomeArquivo);

// Carrega um arquivo de texto
char* carregarArquivo(const char *nomeArquivo, long *tamanho);

// Salva texto em arquivo
void salvarArquivo(const char *nomeArquivo, const char *texto);

#endif