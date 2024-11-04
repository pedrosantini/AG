#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "MatrizEsparsa.h"


int main()
{
    Tipo_Mat_Esparsa *m1 = criar_matrix();

    
    inserir_tipo_elemento(0, 0, 1, m1);

    inserir_tipo_elemento(0, 1, 2, m1);

    inserir_tipo_elemento(1, 0, 3, m1);

    printf("\nqt col %d qt lin %d\n", m1->qtd_colunas, m1->qtd_linhas);

    inserir_tipo_elemento(1, 1, 4, m1); // nao ta funcionando a poha do inserir -(00,00), (00,01), (10,00),(10,10), (10,11)

    inserir_tipo_elemento(2, 0, 5, m1);

    imprmir_matrix(m1);

    Tipo_Mat_Esparsa *m2 = criar_matrix();

    inserir_tipo_elemento(0, 0, 5, m2);

    inserir_tipo_elemento(0, 1, 6, m2);

    inserir_tipo_elemento(1, 0, 7, m2);

    printf("\nqt col %d qt lin %d\n", m2->qtd_colunas, m2->qtd_linhas);

    inserir_tipo_elemento(1, 1, 8, m2); 

    imprmir_matrix(m2);

    Tipo_Mat_Esparsa *r = criar_matrix();

    multiplica_matrixes(m1,m2,r);

    imprmir_matrix(r);

    Tipo_Mat_Esparsa *trans = criar_matrix();

    cria_transposta(m1, trans);

    imprmir_matrix(trans);

    printf("matrix apagada ---->%d<-------", apaga_matrix(m1));

    printf("matriz vazia ---->%d<------", matrix_vazia(m1));

    imprmir_matrix(m1);

    printf("\nopa");

    return 0;
}
/*
int main()
{
    Tipo_Mat_Esparsa *m1 = criar_matrix();
    inserir_tipo_elemento(1, 1, 1, m1);

    inserir_tipo_elemento(1, 2, 2, m1);

    inserir_tipo_elemento(2, 1, 3, m1);

    inserir_tipo_elemento(2, 2, 4, m1);


    printf("\n");

    imprmir_matrix(m1);

    printf("\n \n");

    Tipo_Mat_Esparsa *m2 = criar_matrix();

    inserir_tipo_elemento(0, 0, 5, m2);

    inserir_tipo_elemento(0, 1, 6, m2);
    
    inserir_tipo_elemento(1, 0, 7, m2);

    inserir_tipo_elemento(1, 1, 8, m2);

    imprmir_matrix(m2);

    Tipo_Mat_Esparsa *r = criar_matrix();

    multiplica_matrixes(m1, m2, r);

    imprmir_matrix(r);

    printf("\n \n");

    

    //printf("\n a matriz esta vazia ->%d<- ", matrix_vazia(m));


    return 0;
    
}*/