#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <sys/types.h>

int *serieFibonacci; // Números da série de Fibonacci.
int quantidadeNumeros; // Quantidade de números da série de Fibonacci.
// Gera os números da série de Fibonacci e armazena na região de memória compartilhada.
void *fibonacci(void *quantidadeTermos) {
// Obtém a quantidade de números a ser gerada para série.
    quantidadeNumeros = fabs(atoi((char *) quantidadeTermos));
// Verifica se há pelo menos um número a ser gerado.
    if (quantidadeNumeros > 0) {
// Cria espaço de memória para armazenar os números da série.
        serieFibonacci = (int *) malloc(quantidadeNumeros * sizeof(int));
// Gera os números da série
        serieFibonacci[0] = 0;
        if (quantidadeNumeros >= 2) {
            serieFibonacci[1] = 1;
            for (int n = 2; n < quantidadeNumeros; n++)
                serieFibonacci[n] = serieFibonacci[n - 1] + serieFibonacci[n - 2];
        }
    }
    pthread_exit(0);
}

// Exibe os números da série de Fibonacci.
void exibirSerieFibonacci() {
    int n;
    if (quantidadeNumeros > 0) {
        for (n = 0; n < quantidadeNumeros - 1; n++)
            printf("%d, ", serieFibonacci[n]);
        printf("%d", serieFibonacci[n]);
    }
}

int main(int argc, char *argv[]) {
    pthread_t threadFibonacci; // Identificação da thread.
    pthread_attr_t atrThreadFibonacci; // Atributos das thread.
// Verifica se a quantidade de números da série foi fornecida para o programa.
    if (argc == 2) {
        fibonacci(argv[1]);
// Inicializa a thread com os valores de atributo padrão.
        pthread_attr_init(&atrThreadFibonacci);
// Cria a thread que gera os números da série de fibonacci.
        pthread_create(&threadFibonacci, &atrThreadFibonacci, fibonacci, argv[1]);
// O programa (thread mãe) espera que a thread filha fibonacci termine.
        pthread_join(threadFibonacci, NULL);
// O programa (thread mãe) exibe a série de fibonacci.
        exibirSerieFibonacci();
    } else
        printf("Forneça a quantidade de números da série de Fibonacci. Exemplo: c:\\>fibonacci 5\n");
// Verifica se há memória a ser devolvida para o sistema.
    if (quantidadeNumeros > 0) free(serieFibonacci);
    return 0;
} // main()