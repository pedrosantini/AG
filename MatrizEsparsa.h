#include <stdio.h>
#include <stdlib.h>

typedef struct Tipo_Mat_Esparsa Tipo_Mat_Esparsa;
typedef struct tipo_elemento tipo_elemento;
typedef struct tipo_linha tipo_linha;

int coluna_existe(Tipo_Mat_Esparsa *m, int key);
Tipo_Mat_Esparsa *criar_matrix();
int matrix_vazia(Tipo_Mat_Esparsa *m);
void inserir_tipo_linha(Tipo_Mat_Esparsa *m, int c);
void inserir_tipo_elemento(int l, int c, int v, Tipo_Mat_Esparsa *m);
void busca_elemento(Tipo_Mat_Esparsa);
void imprmir_matrix(Tipo_Mat_Esparsa *m);


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
        Tipo_Mat_Esparsa* mat = (Tipo_Mat_Esparsa*) calloc(sizeof(Tipo_Mat_Esparsa),1);     

        
        mat->qtd_colunas = 0;
        mat->qtd_linhas = 0;

        return mat;
}

void inserir_tipo_linha(Tipo_Mat_Esparsa *m, int c){
    if(!matrix_vazia(m)){
        if(!coluna_existe(m, c)){
            if(m->qtd_colunas < c){
                tipo_linha *aux = m->inicio;
                tipo_linha *nova = (tipo_linha*)calloc(sizeof(tipo_linha), 1);
                while(aux->proximo != NULL)
                    aux = aux->proximo;
                aux->proximo = nova;
                nova->ID_Coluna = c;
                m->qtd_colunas = c;

                printf("\ncoluna %d alocada.", c);
            }
            else if(m->inicio->ID_Coluna > c){
                tipo_linha *nova = (tipo_linha*)calloc(sizeof(tipo_linha), 1);

                tipo_linha *aux = m->inicio;
                m->inicio = nova;
                nova->proximo = aux;
                
                m->inicio = nova;
                nova->ID_Coluna = c;

                printf("\ncoluna %d alocada.", c);
            }
            else{
                tipo_linha *aux = m->inicio;
                while ((aux->proximo->ID_Coluna < c) && (aux->proximo != NULL)){
                    aux = aux->proximo;
                    //printf("aqui chega col %d", aux->proximo->ID_Coluna);
                }
            
                tipo_linha *nova = (tipo_linha*)calloc(sizeof(tipo_linha), 1);

                nova->proximo = aux->proximo;
                aux->proximo = nova;
                nova->ID_Coluna = c;
                

                printf("\ncoluna %d alocada.", c);            
            }
        }
    }
    else{
        tipo_linha *nova = (tipo_linha*)calloc(sizeof(tipo_linha), 1);
        
        m->inicio = nova;
        nova->ID_Coluna = c;
        m->qtd_colunas = c;

        printf("coluna %d alocada.", c);
    }
}

int coluna_existe(Tipo_Mat_Esparsa *m, int key){
    if(!matrix_vazia(m)){
        tipo_linha *x = m->inicio;
        while((key != x->ID_Coluna) && (x->proximo != NULL))
            x = x->proximo;
        
        if(key == x->ID_Coluna)
            return 1;

        return 0;
    }
    return 0;
}

void inserir_tipo_elemento(int l, int c, int v, Tipo_Mat_Esparsa *m){
    if(!matrix_vazia(m)){
        if(coluna_existe(m, c)){

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
            if(l > m->qtd_linhas)
                m->qtd_linhas = l;
            
        }
    }
    else{
        inserir_tipo_linha(m, c);
        tipo_elemento *novo = (tipo_elemento*)calloc(sizeof(tipo_elemento), 1);

        novo->ID_Linha = l;
        novo->valor = v;
        m->inicio->inicio = novo;
        m->qtd_linhas = l;
    } 
}

void imprmir_matrix(Tipo_Mat_Esparsa *m){
    tipo_linha *auxc = m->inicio;
    int matrix[m->qtd_linhas][m->qtd_colunas];
    
    for(int i=0; i < m->qtd_linhas; i++){
        for(int j=0; j < m->qtd_colunas; j++){
            matrix[i][j] = 0;
        }
    }
    

    tipo_elemento *auxl;
    while(auxc != NULL){
        auxl = auxc->inicio;
        while(auxl != NULL){
            matrix[(auxl->ID_Linha)-1][(auxc->ID_Coluna)-1] = auxl->valor;
            printf("foi salvo o elemento %d na linha %d e coluna %d\n", auxl->valor, auxl->ID_Linha, auxc->ID_Coluna);
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

int matrix_vazia(Tipo_Mat_Esparsa *m){
    if((m->inicio == NULL))
        return 1;
    return 0;
}
