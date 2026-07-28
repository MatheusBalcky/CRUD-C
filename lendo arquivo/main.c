#include <stdio.h>
#include <stdlib.h>


int main(void) {

    FILE *f = fopen("arq.txt", "r"); //Abre o arquivo para leitura

    char c;

    if (f == NULL) {

        printf("Arquivo não encontrado.\n");

        return (EXIT_FAILURE);

    }

    while((c = fgetc(f)) != EOF) {
        printf("%c", c);
    }

    printf("\n");

    fclose(f);
    
    return (EXIT_SUCCESS);
}