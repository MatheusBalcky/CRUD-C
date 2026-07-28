#include <stdio.h>
#include <stdlib.h>

int main (void){
    FILE *file = fopen("arq.txt", "w");

    if(file == NULL){
        printf("Arquivo não encontrado"); 
        return (EXIT_FAILURE);
    }

    fputs("**********INICIO**********\n", file);

    char c;
    while((c = getchar()) != EOF) fputc(c, file);

    fputs("**********FIM**********\n", file);

    fclose(file);

    return 0;
}