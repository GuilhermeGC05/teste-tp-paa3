#include "cifra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void inicializarChave(Chave *chave) {
    for (int i = 0; i < TAMANHO_ALFABETO; i++) {
        chave->mapeamento[i] = '\0';
        chave->descoberto[i] = 0;
    }
}

void criptografarDeslocamento(const char *textoClaro, char *textoCifrado, int deslocamento) {
    int i = 0;
    while (textoClaro[i] != '\0') {
        if (isalpha(textoClaro[i])) {
            char base = isupper(textoClaro[i]) ? 'A' : 'a';
            textoCifrado[i] = ((textoClaro[i] - base + deslocamento) % 26 + 26) % 26 + base;
        } else {
            textoCifrado[i] = textoClaro[i];
        }
        i++;
    }
    textoCifrado[i] = '\0';
}

void decifrarTexto(const char *textoCifrado, char *textoDecifrado, const Chave *chave) {
    int i = 0;
    while (textoCifrado[i] != '\0') {
        if (isalpha(textoCifrado[i])) {
            char c = toupper(textoCifrado[i]);
            int indice = c - 'A';
            
            // Procura o índice onde c aparece no mapeamento
            int indiceCifrado = -1;
            for (int j = 0; j < TAMANHO_ALFABETO; j++) {
                if (chave->descoberto[j] && toupper(chave->mapeamento[j]) == c) {
                    indiceCifrado = j;
                    break;
                }
            }
            
            if (indiceCifrado != -1) {
                char letraOriginal = 'A' + indiceCifrado;
                textoDecifrado[i] = isupper(textoCifrado[i]) ? letraOriginal : tolower(letraOriginal);
            } else {
                textoDecifrado[i] = textoCifrado[i];
            }
        } else {
            textoDecifrado[i] = textoCifrado[i];
        }
        i++;
    }
    textoDecifrado[i] = '\0';
}

void adicionarMapeamento(Chave *chave, char original, char cifrado) {
    int indice = toupper(original) - 'A';
    if (indice >= 0 && indice < TAMANHO_ALFABETO) {
        chave->mapeamento[indice] = toupper(cifrado);
        chave->descoberto[indice] = 1;
    }
}

void exibirChave(const Chave *chave) {
    printf("\n=== Chave ===\n");
    for (int i = 0; i < TAMANHO_ALFABETO; i++) {
        printf("%c ", 'A' + i);
    }
    printf("\n");
    for (int i = 0; i < TAMANHO_ALFABETO; i++) {
        if (chave->descoberto[i]) {
            printf("%c ", chave->mapeamento[i]);
        } else {
            printf("  ");
        }
    }
    printf("\n");
}

void salvarChave(const Chave *chave, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (!arquivo) {
        printf("Erro ao abrir arquivo para escrita.\n");
        return;
    }
    
    fprintf(arquivo, "Chave de Criptografia:\n\n");
    fprintf(arquivo, "Original: ");
    for (int i = 0; i < TAMANHO_ALFABETO; i++) {
        fprintf(arquivo, "%c ", 'A' + i);
    }
    fprintf(arquivo, "\nCifrado:  ");
    for (int i = 0; i < TAMANHO_ALFABETO; i++) {
        if (chave->descoberto[i]) {
            fprintf(arquivo, "%c ", chave->mapeamento[i]);
        } else {
            fprintf(arquivo, "? ");
        }
    }
    fprintf(arquivo, "\n\nMapeamentos descobertos:\n");
    for (int i = 0; i < TAMANHO_ALFABETO; i++) {
        if (chave->descoberto[i]) {
            fprintf(arquivo, "%c -> %c\n", 'A' + i, chave->mapeamento[i]);
        }
    }
    
    fclose(arquivo);
    printf("Chave salva em %s\n", nomeArquivo);
}

char* carregarArquivo(const char *nomeArquivo, long *tamanho) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir arquivo %s\n", nomeArquivo);
        return NULL;
    }
    
    fseek(arquivo, 0, SEEK_END);
    *tamanho = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);
    
    char *buffer = (char*)malloc(*tamanho + 1);
    if (!buffer) {
        fclose(arquivo);
        return NULL;
    }
    
    fread(buffer, 1, *tamanho, arquivo);
    buffer[*tamanho] = '\0';
    
    fclose(arquivo);
    return buffer;
}

void salvarArquivo(const char *nomeArquivo, const char *texto) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (!arquivo) {
        printf("Erro ao abrir arquivo para escrita.\n");
        return;
    }
    
    fprintf(arquivo, "%s", texto);
    fclose(arquivo);
    printf("Texto salvo em %s\n", nomeArquivo);
}