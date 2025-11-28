#include "frequencia.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void calcularFrequencia(const char *texto, FrequenciaLetra *frequencias) {
    int contagens[26] = {0};
    int totalLetras = 0;
    
    // Inicializa o array de frequências
    for (int i = 0; i < 26; i++) {
        frequencias[i].letra = 'A' + i;
        frequencias[i].contagem = 0;
        frequencias[i].frequencia = 0.0;
    }
    
    // Conta as letras
    for (int i = 0; texto[i] != '\0'; i++) {
        if (isalpha(texto[i])) {
            int indice = toupper(texto[i]) - 'A';
            contagens[indice]++;
            totalLetras++;
        }
    }
    
    // Calcula as frequências
    for (int i = 0; i < 26; i++) {
        frequencias[i].contagem = contagens[i];
        if (totalLetras > 0) {
            frequencias[i].frequencia = (double)contagens[i] * 100.0 / totalLetras;
        }
    }
}

void ordenarFrequencias(FrequenciaLetra *frequencias) {
    for (int i = 0; i < 25; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (frequencias[j].contagem > frequencias[i].contagem) {
                FrequenciaLetra temp = frequencias[i];
                frequencias[i] = frequencias[j];
                frequencias[j] = temp;
            }
        }
    }
}

void exibirFrequencias(const FrequenciaLetra *frequencias) {
    printf("\n=== Análise de Frequência ===\n");
    printf("Letra | Contagem | Frequência\n");
    printf("------|----------|------------\n");
    
    for (int i = 0; i < 26; i++) {
        if (frequencias[i].contagem > 0) {
            printf("  %c   |   %4d   |   %6.2f%%\n", 
                   frequencias[i].letra, 
                   frequencias[i].contagem, 
                   frequencias[i].frequencia);
        }
    }
}

void adivinharChave(const FrequenciaLetra *frequencias, Chave *chave) {
    // Cria um array com as letras do português ordenadas por frequência
    char letrasPortugues[26];
    FrequenciaLetra freqPort[26];
    
    for (int i = 0; i < 26; i++) {
        freqPort[i].letra = 'A' + i;
        freqPort[i].frequencia = FREQ_PORTUGUES[i];
        freqPort[i].contagem = (int)(FREQ_PORTUGUES[i] * 1000);
    }
    
    // Ordena as letras do português por frequência
    for (int i = 0; i < 25; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (freqPort[j].frequencia > freqPort[i].frequencia) {
                FrequenciaLetra temp = freqPort[i];
                freqPort[i] = freqPort[j];
                freqPort[j] = temp;
            }
        }
    }
    
    printf("\n=== Tentativa de Mapeamento por Frequência ===\n");
    printf("Português | Cifrado\n");
    printf("----------|--------\n");
    
    // Mapeia as letras mais frequentes do texto cifrado com as do português
    for (int i = 0; i < 26; i++) {
        if (frequencias[i].contagem > 0) {
            adicionarMapeamento(chave, freqPort[i].letra, frequencias[i].letra);
            printf("    %c     |   %c\n", freqPort[i].letra, frequencias[i].letra);
        }
    }
    
    printf("\nChave atualizada baseada em análise de frequência.\n");
}