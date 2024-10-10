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
    
    printf("\nqt col %d", m->qtd_colunas);
    return 0;

    free(m);
}
