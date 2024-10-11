#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "MatrizEsparsa.h"

int main()
{
    Tipo_Mat_Esparsa *m = criar_matrix();
    inserir_tipo_elemento(2, 4, 15, m);

    inserir_tipo_elemento(2, 9, 12, m);

    inserir_tipo_elemento(2, 2, 12, m);

    inserir_tipo_elemento(5, 7, 10, m);

    inserir_tipo_elemento(4, 7, 2, m);

    inserir_tipo_elemento(7, 3, 15, m);

    inserir_tipo_elemento(3, 7, 3, m);


    printf("\n");

    imprmir_matrix(m);

    printf("\n \n");

    inserir_tipo_elemento(5, 7, 15, m);

    imprmir_matrix(m);

    printf("\nqt col %d qt lin %d", m->qtd_colunas, m->qtd_linhas);

    return 0;

    
}
