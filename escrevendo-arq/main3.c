#include <stdio.h>
#include <stdlib.h>

int main(void) {

    int elementosEscritos, v[10] = {1,2,3,4,5,6,7,8,9,10};

    FILE *f = fopen("v.dat", "wb"); 

    if (f == NULL) {

        printf("O arquivo não pode ser aberto.\n");
        return (EXIT_FAILURE);

    }

    /* Poderíamos escrever também

    // elementosEscritos = fwrite(v, sizeof(v), 1, f); */

    elementosEscritos = fwrite(v, sizeof(int), 10, f);

    printf("Elementos escritos: %d\n", elementosEscritos);

    fclose(f);

    return (EXIT_SUCCESS);

}