#include <stdio.h>
#include <stdlib.h> // Requerido por exit.
#include <unistd.h> // Requerido por fork e getpid.
#include <sys/wait.h> // Requerido por wait.
#include <string.h>

#define PROCESS_IDENTIFIERS "ABCDEF"

int criarProcesso() {
    // Cria o processo filho.
    int pid = fork();

    // Verifica se ocorreu um erro na criação do processo filho.
    if (pid < 0) {
        printf("\n\nERRO: o processo filho não foi criado.\n\n");
        exit(-1);
    }
    return pid;
}

int arvoreProcessos(){

    int pid;
    int status;

    pid = criarProcesso();

    if(pid != 0){
        printf("\n%d ->  Processo %c executando...\n", getpid(), PROCESS_IDENTIFIERS[0]);

        pid = criarProcesso();
        if(pid  != 0){
            pid = wait(&status);
            printf("\n%d ->  Processo %c finalizado.\n", getpid(), PROCESS_IDENTIFIERS[2]);
            pid = wait(&status);
            printf("\n%d ->  Processo %c finalizado.\n", getpid(), PROCESS_IDENTIFIERS[1]);
            printf("\n%d ->  Processo %c finalizado.\n", getpid(), PROCESS_IDENTIFIERS[0]);
        }
        else{
            printf("\n%d ->  Processo %c executando...\n", getpid(), PROCESS_IDENTIFIERS[2]);
            exit(0);
        }
    }else{
        printf("\n%d ->  Processo %c executando...\n", getpid(), PROCESS_IDENTIFIERS[1]);
        pid = criarProcesso();
        if(pid  != 0){


            pid = criarProcesso();
            if(pid  != 0){


                pid = criarProcesso();
                if(pid  != 0){
                    pid = wait(&status);
                    printf("\n%d ->  Processo %c finalizado.\n", getpid(), PROCESS_IDENTIFIERS[5]);

                    pid = wait(&status);
                    printf("\n%d ->  Processo %c finalizado.\n", getpid(), PROCESS_IDENTIFIERS[4]);

                    pid = wait(&status);
                    printf("\n%d ->  Processo %c finalizado.\n", getpid(), PROCESS_IDENTIFIERS[3]);
                }
                else{
                    printf("\n%d ->  Processo %c executando...\n", getpid(), PROCESS_IDENTIFIERS[5]);
                    exit(0);
                }
            }
            else{
                printf("\n%d ->  Processo %c executando...\n", getpid(), PROCESS_IDENTIFIERS[4]);
                exit(0);
            }
        }
        else{
            printf("\n%d ->  Processo %c executando...\n", getpid(), PROCESS_IDENTIFIERS[3]);
            exit(0);
        }
        exit(0);
    }
    return 0;
}

int main(){
    return arvoreProcessos();
}
