#ifndef CASAMENTO_H
#define CASAMENTO_H

#define MAX_OCORRENCIAS 1000

typedef struct {
    int posicao;
    char texto[256];
} Ocorrencia;

// Algoritmo KMP para casamento exato
int casamentoExatoKMP(const char *texto, const char *padrao, Ocorrencia *ocorrencias);

// Algoritmo Shift-And aproximado para casamento aproximado
int casamentoAproximadoShiftAnd(const char *texto, const char *padrao, int k, Ocorrencia *ocorrencias);

// Exibe as ocorrências encontradas
void exibirOcorrencias(const Ocorrencia *ocorrencias, int numOcorrencias, const char *padrao);

#endif