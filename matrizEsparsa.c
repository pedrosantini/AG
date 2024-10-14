#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "MatrizEsparsa.h"

/*
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

    inserir_tipo_elemento(0, 0, 33, m);

    imprmir_matrix(m);

    printf("\n-----Valor encontrado %d------", busca_elemento(m, 5, 7));    

    printf("\nqt col %d qt lin %d\n", m->qtd_colunas, m->qtd_linhas);

    printf("-----%d--------\n", apaga_matrix(m));

    printf("\nqt col %d qt lin %d\n", m->qtd_colunas, m->qtd_linhas);

    imprmir_matrix(m);

    printf("\n \n");

    //printf("\n a matriz esta vazia ->%d<- ", matrix_vazia(m));


    return 0;
    
}*/
int main()
{
    Tipo_Mat_Esparsa *m1 = criar_matrix();
    inserir_tipo_elemento(2, 4, 15, m1);

    inserir_tipo_elemento(2, 9, 12, m1);

    inserir_tipo_elemento(2, 2, 12, m1);

    inserir_tipo_elemento(5, 7, 10, m1);

    inserir_tipo_elemento(4, 7, 2, m1);

    inserir_tipo_elemento(7, 3, 15, m1);

    inserir_tipo_elemento(3, 7, 3, m1);


    printf("\n");

    imprmir_matrix(m1);

    printf("\n \n");

    Tipo_Mat_Esparsa *m2 = criar_matrix();
    inserir_tipo_elemento(2, 4, 15, m2);

    inserir_tipo_elemento(2, 9, 12, m2);// apague essa linha para as matrizes terem dim diferentes

    inserir_tipo_elemento(5, 7, 10, m2);

    inserir_tipo_elemento(7, 3, 15, m2);



    printf("\n");

    imprmir_matrix(m2);

    printf("\n \n");

    Tipo_Mat_Esparsa *r = criar_matrix();

    printf("\n \n");

    soma_matrixes(m1, m2, r);

    printf("\n \n");

    imprmir_matrix(r);

    //printf("\n a matriz esta vazia ->%d<- ", matrix_vazia(m));
    return 0;
}