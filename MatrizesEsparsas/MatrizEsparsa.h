#include <stdio.h>
#include <stdlib.h>

typedef struct Tipo_Mat_Esparsa Tipo_Mat_Esparsa;
typedef struct tipo_elemento tipo_elemento;
typedef struct tipo_linha tipo_linha;

int coluna_existe(Tipo_Mat_Esparsa *m, int key);
int linha_existe(Tipo_Mat_Esparsa *m, int c, int key);
Tipo_Mat_Esparsa *criar_matrix();
int matrix_vazia(Tipo_Mat_Esparsa *m);
void inserir_tipo_linha(Tipo_Mat_Esparsa *m, int c);
void inserir_tipo_elemento(int l, int c, int v, Tipo_Mat_Esparsa *m);
int busca_elemento(Tipo_Mat_Esparsa *m, int l, int c);
int elemento_existe(Tipo_Mat_Esparsa *m, int l, int c); //retorna -1 se a matriz esta vazia, retorna 1 se o elemento existe, retorna 0 se o elemento nao existe
void imprmir_matrix(Tipo_Mat_Esparsa *m);

//-----------------------

int apaga_matrix(Tipo_Mat_Esparsa *m);
void cria_transposta(Tipo_Mat_Esparsa *m1, Tipo_Mat_Esparsa *r);
void soma_matrixes(Tipo_Mat_Esparsa *m1, Tipo_Mat_Esparsa *m2, Tipo_Mat_Esparsa *r);
void multiplica_matrixes(Tipo_Mat_Esparsa *m1, Tipo_Mat_Esparsa *m2, Tipo_Mat_Esparsa *r);

//-----------------------
typedef struct tipo_elemento{
    int valor;
    int ID_Linha;
    struct tipo_elemento *proximo;    
}tipo_elemento;

typedef struct tipo_linha{
    int ID_Coluna;
    struct tipo_linha *proximo;
    struct tipo_elemento *inicio;
}tipo_linha;

typedef struct Tipo_Mat_Esparsa{
    int qtd_linhas;
    int qtd_colunas;
    struct tipo_linha *inicio;
}Tipo_Mat_Esparsa;

Tipo_Mat_Esparsa* criar_matrix(){
        Tipo_Mat_Esparsa* mat = (Tipo_Mat_Esparsa*) calloc(sizeof(Tipo_Mat_Esparsa), 1);     
        
        mat->qtd_colunas = 0;
        mat->qtd_linhas = 0;

        return mat;
}

void inserir_tipo_linha(Tipo_Mat_Esparsa *m, int c){
    if(!matrix_vazia(m)){
        if(!coluna_existe(m, c)){
            if(m->qtd_colunas-1 < c){
                tipo_linha *aux = m->inicio;
                tipo_linha *nova = (tipo_linha*)calloc(1, sizeof(tipo_linha));
                while(aux->proximo != NULL)
                    aux = aux->proximo;
                aux->proximo = nova;
                nova->ID_Coluna = c;
                m->qtd_colunas = c+1;

                //printf("\ncoluna %d alocada.", c);
            }
            else if(m->inicio->ID_Coluna > c){
                tipo_linha *nova = (tipo_linha*)calloc(1, sizeof(tipo_linha));

                tipo_linha *aux = m->inicio;
                m->inicio = nova;
                nova->proximo = aux;                
                nova->ID_Coluna = c;

                //printf("\ncoluna %d alocada.", c);
            }
            else{
                tipo_linha *aux = m->inicio;
                while ((aux->proximo->ID_Coluna < c) && (aux->proximo != NULL))
                    aux = aux->proximo;
                
            
                tipo_linha *nova = (tipo_linha*)calloc(sizeof(tipo_linha), 1);

                nova->proximo = aux->proximo;
                aux->proximo = nova;
                nova->ID_Coluna = c;
                

                //printf("\ncoluna %d alocada.", c);            
            }
        }
    }
    else{
        tipo_linha *nova = (tipo_linha*)calloc(sizeof(tipo_linha), 1);
        
        m->inicio = nova;
        nova->ID_Coluna = c;
        m->qtd_colunas = c+1;

        //printf("coluna %d alocada.", c);
    }
}

int coluna_existe(Tipo_Mat_Esparsa *m, int key){
    if(!matrix_vazia(m)){
        tipo_linha *x = m->inicio;
        while((key != x->ID_Coluna) && (x->proximo != NULL))
            x = x->proximo;
        
        if(key == x->ID_Coluna)
            return 1;
    }
    return 0;
}

int linha_existe(Tipo_Mat_Esparsa *m, int c, int key){
    if(coluna_existe(m, c)){
        tipo_linha *auxc = m->inicio;
        while(auxc->ID_Coluna != c)
            auxc = auxc->proximo;
        
        tipo_elemento *auxl = auxc->inicio;
        while((auxl->proximo != NULL) && (auxl->ID_Linha != key))
            auxl = auxl->proximo;
        if(auxl->ID_Linha == key)
            return 1;
    }
    return 0;
}


void inserir_tipo_elemento(int l, int c, int v, Tipo_Mat_Esparsa *m){
    if(v != 0){
        if(!matrix_vazia(m)){
            if(coluna_existe(m, c)){
                tipo_linha *auxc = m->inicio;
                while(c != auxc->ID_Coluna)
                    auxc = auxc->proximo;
                if(!linha_existe(m, auxc->ID_Coluna, l)){
                    if(auxc->inicio->ID_Linha > l){
                        tipo_elemento *novo = (tipo_elemento*)calloc(sizeof(tipo_elemento), 1);

                        tipo_elemento *aux = auxc->inicio;
                        auxc->inicio = novo;
                        novo->proximo = aux;
                        novo->valor = v;
                        
                        novo->ID_Linha = l;

                        //printf("\nlinha %d alocada.", l);
                    }
                    else if(m->qtd_linhas-1 < l){
                        tipo_elemento *novo = (tipo_elemento*)calloc(sizeof(tipo_elemento), 1);
                        tipo_elemento *aux = auxc->inicio;
                        while(aux->proximo != NULL)
                            aux = aux->proximo;
                        
                        aux->proximo = novo;
                        novo->ID_Linha = l;
                        novo->valor = v;
                        m->qtd_linhas = l+1;
                        
                    }
                    else{
                        tipo_elemento *novo = (tipo_elemento*)calloc(sizeof(tipo_elemento), 1);
                        tipo_elemento *aux = auxc->inicio;
                        if (aux->proximo != NULL)
                            while ((aux->proximo->ID_Linha < c) && (aux->proximo != NULL))
                                aux = aux->proximo;
                        
                        
                        novo->proximo = aux->proximo;
                        aux->proximo = novo;
                        novo->ID_Linha = l;
                        novo->valor = v;

                    }                
                }
                else{
                    tipo_elemento *aux = auxc->inicio;
                    while(aux->ID_Linha != l)
                        aux = aux->proximo;
                    
                    aux->valor = v;
                }       
            }
            else{
                inserir_tipo_linha(m, c);
                tipo_elemento *novo = (tipo_elemento*)calloc(sizeof(tipo_elemento), 1);
                tipo_linha *aux = m->inicio;

                
                while(c != aux->ID_Coluna)
                    aux = aux->proximo;
                
                
                aux->inicio = novo;
                novo->ID_Linha = l;
                novo->valor = v;
                if(l > m->qtd_linhas-1)
                    m->qtd_linhas = l+1;
                
            }
        }
        else{
            inserir_tipo_linha(m, c);
            tipo_elemento *novo = (tipo_elemento*)calloc(sizeof(tipo_elemento), 1);

            novo->ID_Linha = l;
            novo->valor = v;
            m->inicio->inicio = novo;
            m->qtd_linhas = l+1;
        }
    }
}


void imprmir_matrix(Tipo_Mat_Esparsa *m){
    if (!matrix_vazia(m)){
        tipo_linha *auxc = m->inicio;
        int **matrix = (int**)calloc(sizeof(int*), m->qtd_linhas);
        
        for(int i=0; i < m->qtd_linhas; i++){
            matrix[i] = (int*)calloc(sizeof(int), m->qtd_colunas);
        }
        //printf("\n l %d -- c %d", m->qtd_linhas, m->qtd_colunas);

        tipo_elemento *auxl;
        while(auxc != NULL){
            auxl = auxc->inicio;
            while(auxl != NULL){
                matrix[auxl->ID_Linha][auxc->ID_Coluna] = auxl->valor;
                //printf("foi salvo o elemento %d na linha %d e coluna %d\n", auxl->valor, auxl->ID_Linha, auxc->ID_Coluna);
                auxl = auxl->proximo;
            }
            auxc = auxc->proximo;
        }

        for(int i=0; i < m->qtd_linhas; i++){
            for(int j=0; j < m->qtd_colunas; j++){
                printf("%3d ", matrix[i][j]);
            }
            printf("\n");
        }
        

    }
    else{
        printf("A MATRIZ ESTA VAZIA!\n");
    }
    
}

int busca_elemento(Tipo_Mat_Esparsa *m, int l, int c){
    if(elemento_existe(m, l, c) == 1){
        tipo_linha *auxc = m->inicio;
        while(auxc->ID_Coluna != c)
            auxc = auxc->proximo;
        tipo_elemento *auxl = auxc->inicio;
        while(auxl->ID_Linha != l)
            auxl = auxl->proximo;
        return auxl->valor;
    }
    return 0;
}

int elemento_existe(Tipo_Mat_Esparsa *m, int l, int c){
    if(matrix_vazia(m))
        return -1;
    else if(coluna_existe(m, c))
        if(linha_existe(m, c, l))
            return 1;        
    return 0;
}

int matrix_vazia(Tipo_Mat_Esparsa *m){
    if((m->inicio == NULL))
        return 1;
    return 0;
}


//----------

void soma_matrixes(Tipo_Mat_Esparsa *m1, Tipo_Mat_Esparsa *m2, Tipo_Mat_Esparsa *r){
    if((m1->qtd_linhas == m2->qtd_linhas) && (m1->qtd_colunas == m2->qtd_colunas)){
        if((!matrix_vazia(m1)) && (!matrix_vazia(m2))){
            for(int i=0; i < m1->qtd_linhas; i++){
                for(int j=0; j < m1->qtd_colunas; j++){
                    if((elemento_existe(m1, i, j)) || (elemento_existe(m2, i, j))){
                        inserir_tipo_elemento(i, j, busca_elemento(m1, i, j)+busca_elemento(m2, i, j), r);
                    }
                }
            }
        }
    }
    else{
        printf("AS MATRIZES DEVEM TER A MESMA DIMENSAO PARA SOMAR\n");
    }
}

void multiplica_matrixes(Tipo_Mat_Esparsa *m1, Tipo_Mat_Esparsa *m2, Tipo_Mat_Esparsa *r){
    if((!matrix_vazia(m1)) && (!matrix_vazia(m2))){
        if(m1->qtd_colunas == m2->qtd_linhas){
            int soma, i, j, k;
            for(i=0; i < m1->qtd_linhas; i++){
                for(j=0; j < m2->qtd_colunas; j++){
                    soma = 0;
                    for (k=0; k < m1->qtd_colunas; k++)
                        soma += busca_elemento(m1, i, k)*busca_elemento(m2, k, j);
                        
                    inserir_tipo_elemento(i, j, soma, r);
                }
            }
        }
        else{
            printf("NAO EXISTE MULPLICACAO PARA MATRIZES DESSAS DIMENSÕES\n");
        }
    }
}

int apaga_matrix(Tipo_Mat_Esparsa *m){
    if (!matrix_vazia(m)){
        tipo_linha *auxc;
        tipo_elemento *auxl;
        
        while (m->inicio != NULL){
            auxc = m->inicio;

            m->inicio = auxc->proximo;

            if (auxc->inicio != NULL){
                while (auxc->inicio != NULL){
                    auxl = auxc->inicio;

                    auxc->inicio = auxl->proximo;

                    free(auxl);                    
                }

                free(auxc);
            }

        }

        m->qtd_colunas = 0;
        m->qtd_linhas = 0;

        free(m);

        return 1;
    }
    
    return 0;
}


void cria_transposta(Tipo_Mat_Esparsa *m1, Tipo_Mat_Esparsa *r){
    if (!matrix_vazia(m1)){
        for(int i=0; i < m1->qtd_linhas; i++)
            for(int j=0; j < m1->qtd_colunas; j++)
                if(elemento_existe(m1, i, j))
                    inserir_tipo_elemento(j, i, busca_elemento(m1, i, j),r);    
    }        
}