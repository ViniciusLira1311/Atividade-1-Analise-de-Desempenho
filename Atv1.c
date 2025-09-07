#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <time.h>

int validarEntrada(const char* entrada) {
    // Verifica se a string está vazia
    if (entrada == NULL || strlen(entrada) == 0) {
        return 0;
    }
    
    // Verifica se todos os caracteres são dígitos
    for (int i = 0; entrada[i] != '\0'; i++) {
        if (!isdigit(entrada[i])) {
            return 0;
        }
    }
    
    // Converte para número e verifica se é maior que 0
    int numero = atoi(entrada);
    if (numero <= 0) {
        return 0;
    }
    
    return numero;
}

int contarPrimos(int n) {
    if (n < 2) return 0;
    
    // Aloca memória para o array do crivo
    int* ehPrimo = (int*)malloc((n + 1) * sizeof(int));
    if (ehPrimo == NULL) {
        printf("Erro de alocação de memória!\n");
        return -1;
    }
    
    // Inicializa o array: 0 = não primo, 1 = primo
    for (int i = 0; i <= n; i++) {
        ehPrimo[i] = 1;
    }
    ehPrimo[0] = ehPrimo[1] = 0;
    
    // Aplica o Crivo de Eratóstenes
    int limite = (int)sqrt(n);
    for (int i = 2; i <= limite; i++) {
        if (ehPrimo[i]) {
            for (int j = i * i; j <= n; j += i) {
                ehPrimo[j] = 0;
            }
        }
    }
    
    // Conta os números primos
    int contador = 0;
    for (int i = 2; i <= n; i++) {
        if (ehPrimo[i]) {
            contador++;
        }
    }
    
    // Libera a memória alocada
    free(ehPrimo);
    
    return contador;
}

void mostrarPrimos(int n, int quantidadePrimos) {
    if (n > 1000 || quantidadePrimos == 0) {
        return; // Não mostra primos para N grande
    }
    
    printf("Primos encontrados: ");
    int* ehPrimo = (int*)malloc((n + 1) * sizeof(int));
    
    // Recria o crivo para mostrar os primos
    for (int i = 0; i <= n; i++) {
        ehPrimo[i] = 1;
    }
    ehPrimo[0] = ehPrimo[1] = 0;
    
    int limite = (int)sqrt(n);
    for (int i = 2; i <= limite; i++) {
        if (ehPrimo[i]) {
            for (int j = i * i; j <= n; j += i) {
                ehPrimo[j] = 0;
            }
        }
    }
    
    // Mostra os primos formatados
    int count = 0;
    for (int i = 2; i <= n; i++) {
        if (ehPrimo[i]) {
            printf("%d", i);
            count++;
            if (count < quantidadePrimos) {
                printf(", ");
            }
            if (count % 10 == 0 && count < quantidadePrimos) {
                printf("\n                   ");
            }
        }
    }
    printf("\n");
    
    free(ehPrimo);
}

int main() {
    char entrada[100];
    int n;
    
    printf("==============================================\n");
    printf("CONTADOR DE NUMEROS PRIMOS - CRIVO DE ERATOSTENES\n");
    printf("==============================================\n");
    
    while (1) {
        printf("\nDigite um numero inteiro positivo (ou 'sair' para encerrar): ");
        
        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            printf("Erro na leitura da entrada.\n");
            continue;
        }
        
        // Remove o caractere de nova linha
        entrada[strcspn(entrada, "\n")] = '\0';
        
        // Verifica se o usuário quer sair
        if (strcmp(entrada, "sair") == 0 || strcmp(entrada, "Sair") == 0) {
            printf("Programa encerrado.\n");
            break;
        }
        
        // Valida a entrada
        n = validarEntrada(entrada);
        if (n == 0) {
            printf("Erro: Entrada invalida! Digite um numero inteiro maior que 0.\n");
            continue;
        }
        
        // Mede o tempo de execução
        clock_t inicio = clock();
        int quantidadePrimos = contarPrimos(n);
        clock_t fim = clock();
        double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
        
        // Exibe os resultados
        printf("\nRESULTADO:\n");
        printf("----------------------------------------------\n");
        printf("Numero informado (N): %d\n", n);
        printf("Quantidade de primos entre 1 e %d: %d\n", n, quantidadePrimos);
        printf("Tempo de execucao: %.2f milissegundos\n", tempo);
        printf("----------------------------------------------\n");
        
        // Mostra os primos para N pequeno
        if (n <= 1000) {
            mostrarPrimos(n, quantidadePrimos);
        }
    }
    
    return 0;
}