#include <stdlib.h>
#include <stdio.h>
#define SIZE 100

void atualizar() {

    FILE *f = fopen("arq.txt", "a");

    if (f == NULL) {

    printf("O arquivo não pode ser aberto\n");

    } else {

    fputs("\nAtualizando...\n", f);

    fclose(f);

}

}

void ler() {
    FILE *f = fopen("arq.txt", "r");

    char str[SIZE];

    if (f == NULL) {

        printf("O arquivo não abriu \n");

    } else {

        while (fgets(str, SIZE, f) != NULL) printf("%s", str);    
    }

    fclose(f);
}

int main(void) {

    atualizar();

    ler();

    return (EXIT_SUCCESS);

}