#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <time.h>

int validarEntrada(const char* entrada) {
    if (entrada == NULL || strlen(entrada) == 0) {
        return 0;
    }
    
    for (int i = 0; entrada[i] != '\0'; i++) {
        if (!isdigit(entrada[i])) {
            return 0;
        }
    }
    
    int numero = atoi(entrada);
    if (numero <= 0) {
        return 0;
    }
    
    return numero;
}

int contarPrimos(int n) {
    if (n < 2) return 0;
    
    // Usando calloc para inicializar com zeros
    int* ehPrimo = (int*)calloc(n + 1, sizeof(int));
    if (ehPrimo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return -1;
    }
    
    // Marca todos como primos inicialmente (1 = primo)
    for (int i = 2; i <= n; i++) {
        ehPrimo[i] = 1;
    }
    
    // Crivo de Eratóstenes
    int limite = (int)sqrt(n);
    for (int i = 2; i <= limite; i++) {
        if (ehPrimo[i]) {
            for (int j = i * i; j <= n; j += i) {
                ehPrimo[j] = 0;
            }
        }
    }
    
    // Conta os primos
    int contador = 0;
    for (int i = 2; i <= n; i++) {
        if (ehPrimo[i]) {
            contador++;
        }
    }
    
    free(ehPrimo);
    return contador;
}

void mostrarPrimos(int n) {
    if (n > 1000) {
        return;
    }
    
    printf("Primos encontrados: ");
    int* ehPrimo = (int*)calloc(n + 1, sizeof(int));
    
    for (int i = 2; i <= n; i++) {
        ehPrimo[i] = 1;
    }
    
    int limite = (int)sqrt(n);
    for (int i = 2; i <= limite; i++) {
        if (ehPrimo[i]) {
            for (int j = i * i; j <= n; j += i) {
                ehPrimo[j] = 0;
            }
        }
    }
    
    int count = 0;
    int total = 0;
    
    // Primeiro conta o total para formatar a saída
    for (int i = 2; i <= n; i++) {
        if (ehPrimo[i]) {
            total++;
        }
    }
    
    // Agora mostra os primos
    for (int i = 2; i <= n; i++) {
        if (ehPrimo[i]) {
            printf("%d", i);
            count++;
            if (count < total) {
                printf(", ");
            }
            if (count % 10 == 0 && count < total) {
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
    printf("CONTADOR DE NUMEROS PRIMOS\n");
    printf("==============================================\n");
    
    while (1) {
        printf("\nDigite um numero inteiro positivo (ou 'sair'): ");
        
        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            printf("Erro na leitura!\n");
            continue;
        }
        
        // Remove newline
        entrada[strcspn(entrada, "\n")] = '\0';
        
        if (strcmp(entrada, "sair") == 0 || strcmp(entrada, "Sair") == 0) {
            printf("Programa encerrado.\n");
            break;
        }
        
        n = validarEntrada(entrada);
        if (n == 0) {
            printf("Erro: Digite um numero inteiro maior que 0!\n");
            continue;
        }
        
        // Medir tempo
        clock_t start = clock();
        int qtd_primos = contarPrimos(n);
        clock_t end = clock();
        double tempo = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
        
        printf("\n=== RESULTADO ===\n");
        printf("Numero N: %d\n", n);
        printf("Primos entre 1 e %d: %d\n", n, qtd_primos);
        printf("Tempo: %.3f ms\n", tempo);
        printf("=================\n");
        
        if (n <= 1000 && qtd_primos > 0) {
            mostrarPrimos(n);
        }
    }
    
    return 0;
}