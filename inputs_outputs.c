#include <stdio.h>
#include "inputs_outputs.h"

float inputFloat(char mensagem[]) {
    float valor;

    printf("%s", mensagem);
    scanf("%f", &valor);

    return valor;
}

int inputInt(char mensagem[]) {
    int valor;

    printf("%s", mensagem);
    scanf("%d", &valor);

    return valor;
}

void inputString(char mensagem[], char valor[]) {
    printf("%s", mensagem);
    scanf("%9s", valor); 
}