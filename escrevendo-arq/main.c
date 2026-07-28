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
    FILE *f = fopen("clientes.txt", "w");
    cliente c;
    int ce = 0; 

    if (f == NULL) {
        printf("O arquivo não pode ser aberto.\n");
        return (EXIT_FAILURE);
    }

    printf("Informe o saldo, primeiro e o ultimo nome do cliente:\n");
    c.numero = 0;
    printf("? ");
    scanf("%lf %10s %10s", &c.saldo, c.primeiroNome, c.ultimoNome);

    while (!feof(stdin)) { //ctrl^z para fim de arquivo no Windows

        ce+=fprintf(f, "%d %lf %s %s\n", c.numero++, c.saldo, c.primeiroNome, c.ultimoNome);
        printf("? ");
        scanf("%lf%10s%10s", &c.saldo, c.primeiroNome, c.ultimoNome);
    }

    printf("Foram escritos %d caracteres com sucesso no arquivo\n", ce);
    fclose(f);

    return (EXIT_SUCCESS);
}