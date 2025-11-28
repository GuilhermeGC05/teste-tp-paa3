#ifndef FREQUENCIA_H
#define FREQUENCIA_H

#include "cifra.h"

typedef struct {
    char letra;
    int contagem;
    double frequencia;
} FrequenciaLetra;

// Frequências do português (em porcentagem)
static const double FREQ_PORTUGUES[26] = {
    14.63, 1.04, 3.88, 4.99, 12.57, 1.02, 1.30, 1.28, 6.18, 0.40,
    0.02, 2.78, 4.74, 5.05, 10.73, 2.52, 1.20, 6.53, 7.81, 4.34,
    4.63, 1.67, 0.01, 0.21, 0.01, 0.47
};

// Calcula a frequência de letras no texto
void calcularFrequencia(const char *texto, FrequenciaLetra *frequencias);

// Ordena as frequências em ordem decrescente
void ordenarFrequencias(FrequenciaLetra *frequencias);

// Exibe a tabela de frequências
void exibirFrequencias(const FrequenciaLetra *frequencias);

// Tenta adivinhar a chave baseado em análise de frequência
void adivinharChave(const FrequenciaLetra *frequencias, Chave *chave);

#endif