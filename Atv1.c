#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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

int main() {
    char entrada[100];
    int n;
    
    printf("Digite um número inteiro positivo: ");
    
    // Lê a entrada do usuário de forma segura
    if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
        printf("Erro na leitura da entrada.\n");
        return 1;
    }
    
    // Remove o caractere de nova linha do fgets
    entrada[strcspn(entrada, "\n")] = '\0';
    
    // Chama a função de validação
    n = validarEntrada(entrada);
    
    // Verifica se a entrada é válida
    if (n == 0) {
        printf("Erro: Entrada inválida! Digite um número inteiro maior que 0.\n");
        return 1;
    }
    
    printf("Número válido: %d\n", n);
    
    return 0;
}