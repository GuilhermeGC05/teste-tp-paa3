#include "casamento.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Função auxiliar para criar tabela de falhas do KMP
void computarTabelaKMP(const char *padrao, int m, int *lps) {
    int len = 0;
    lps[0] = 0;
    int i = 1;
    
    while (i < m) {
        if (toupper(padrao[i]) == toupper(padrao[len])) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int casamentoExatoKMP(const char *texto, const char *padrao, Ocorrencia *ocorrencias) {
    int n = strlen(texto);
    int m = strlen(padrao);
    int numOcorrencias = 0;
    
    if (m == 0) return 0;
    
    int *lps = (int*)malloc(m * sizeof(int));
    computarTabelaKMP(padrao, m, lps);
    
    int i = 0; // índice para texto
    int j = 0; // índice para padrao
    
    while (i < n) {
        if (toupper(texto[i]) == toupper(padrao[j])) {
            i++;
            j++;
        }
        
        if (j == m) {
            // Padrão encontrado
            if (numOcorrencias < MAX_OCORRENCIAS) {
                ocorrencias[numOcorrencias].posicao = i - j;
                strncpy(ocorrencias[numOcorrencias].texto, &texto[i - j], m);
                ocorrencias[numOcorrencias].texto[m] = '\0';
                numOcorrencias++;
            }
            j = lps[j - 1];
        } else if (i < n && toupper(texto[i]) != toupper(padrao[j])) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    
    free(lps);
    return numOcorrencias;
}

int casamentoAproximadoShiftAnd(const char *texto, const char *padrao, int k, Ocorrencia *ocorrencias) {
    int n = strlen(texto);
    int m = strlen(padrao);
    int numOcorrencias = 0;
    
    if (m == 0 || m > 31) return 0; // Shift-And limitado a padrões de até 31 caracteres
    
    // Cria máscara de bits para cada caractere
    unsigned int mascara[256];
    for (int i = 0; i < 256; i++) {
        mascara[i] = ~0;
    }
    
    for (int i = 0; i < m; i++) {
        mascara[(unsigned char)toupper(padrao[i])] &= ~(1U << i);
    }
    
    // Array de vetores de estado para cada nível de erro
    unsigned int *R = (unsigned int*)malloc((k + 1) * sizeof(unsigned int));
    
    for (int i = 0; i <= k; i++) {
        R[i] = ~1;
    }
    
    for (int i = 0; i < n; i++) {
        unsigned int oldR[k + 1];
        for (int j = 0; j <= k; j++) {
            oldR[j] = R[j];
        }
        
        // Casamento exato
        R[0] = (oldR[0] << 1) | mascara[(unsigned char)toupper(texto[i])];
        
        // Casamento com erros (substituição)
        for (int j = 1; j <= k; j++) {
            R[j] = ((oldR[j] << 1) | mascara[(unsigned char)toupper(texto[i])]) & 
                   (oldR[j - 1] << 1); // Substituição
        }
        
        // Verifica se houve match com até k erros
        if ((R[k] & (1U << (m - 1))) == 0) {
            if (numOcorrencias < MAX_OCORRENCIAS) {
                int inicio = (i - m + 1 >= 0) ? i - m + 1 : 0;
                int tamanho = i - inicio + 1;
                if (tamanho > 255) tamanho = 255;
                
                ocorrencias[numOcorrencias].posicao = inicio;
                strncpy(ocorrencias[numOcorrencias].texto, &texto[inicio], tamanho);
                ocorrencias[numOcorrencias].texto[tamanho] = '\0';
                numOcorrencias++;
            }
        }
    }
    
    free(R);
    return numOcorrencias;
}

void exibirOcorrencias(const Ocorrencia *ocorrencias, int numOcorrencias, const char *padrao) {
    printf("\nOcorrências encontradas: %d\n", numOcorrencias);
    
    if (numOcorrencias > 0) {
        printf("\nDetalhes:\n");
        for (int i = 0; i < numOcorrencias && i < 50; i++) {
            printf("Posição %d: %s\n", ocorrencias[i].posicao, ocorrencias[i].texto);
        }
        
        if (numOcorrencias > 50) {
            printf("... e mais %d ocorrências\n", numOcorrencias - 50);
        }
    }
}