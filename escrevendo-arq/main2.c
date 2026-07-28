#include <stdio.h>
#include <stdlib.h>

struct clienteStr {
    int numero;
    double saldo;
    char primeiroNome[10];
    char ultimoNome[10];
};

typedef struct clienteStr cliente;

int main(void) {
    cliente c;
    FILE *f = fopen("clientes.txt", "r");

    if (f == NULL) {
        printf("O arquivo não pode ser aberto.\n");
        return (EXIT_FAILURE);
    }

    while (fscanf(f, "%d%lf%s%s", &c.numero, &c.saldo, c.primeiroNome, c.ultimoNome)!= EOF){
        printf("%d %.2lf %s %s\n", c.numero, c.saldo, c.primeiroNome, c.ultimoNome);
    }

    fclose(f);
    return (EXIT_SUCCESS);
}