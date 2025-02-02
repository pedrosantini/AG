#include <stdio.h>
#include <stdlib.h>

typedef struct grafo grafo;
typedef struct vertice vertice;
typedef struct aresta aresta;

int grafo_nulo(grafo *g);
int buscar_vert(int id, grafo *g);
int buscar_aresta(int v1, int v2, grafo *g);
void insert_vertice(int id, grafo *g);
void insert_aresta(int v1, int v2, int peso, grafo *g);
void visualizar_grafo(grafo *g);
void remover_vertices(int id, grafo *g);
void remover_aresta(int v1, int v2, grafo *g);
int informa_grau(int v1, int v2, grafo *g);
int grafo_conexo(grafo *g);
void conv_mat_adj(grafo *g);
int qtd_v(grafo *g);
int qtd_a(grafo *g);
int busca_em_profundidade(vertice *v, int *verticesVisitados, grafo *g);




typedef struct grafo{
    vertice *inicio;
    
}grafo;

typedef struct vertice{
    aresta *a;
    vertice *next;
    int id;
}vertice;

typedef struct aresta{
    int aid;
    int p;
    aresta *prox;

}aresta;

grafo *criar_grafo(){
    grafo *g = (grafo*)calloc(sizeof(grafo), 1);

    g->inicio = NULL;

    return g;
}

int grafo_nulo(grafo *g){
    if (g->inicio == NULL)
        return 1;
    return 0;
}

void insert_vertice(int x, grafo *g){
    if (!grafo_nulo(g)){
        if (!buscar_vert(x, g)){
            vertice *aux = g->inicio;
            while(aux->next != NULL)
                aux = aux->next;
            aux->next = (vertice*)calloc(sizeof(vertice), 1);
            aux->next->id = x;
            
        }
        else
            printf("vertice ja existe\n");
    }
    else{
        g->inicio = (vertice*)calloc(sizeof(vertice), 1);
        g->inicio->id = x;
    }
}

void insert_aresta(int v1, int v2, int peso, grafo *g){ 
    if(!grafo_nulo(g)){   
        if (v2 != v1){          
            if (!buscar_aresta(v1, v2, g)){
                if (buscar_vert(v1, g) && buscar_vert(v2, g)){
                    vertice *auxV1 = g->inicio;
                    vertice *auxV2 = g->inicio;

                    

                    while ((auxV1->id != v1) || (auxV2->id != v2)){
                        if(auxV1->id != v1)
                            auxV1 = auxV1->next;
                        
                        if (auxV2->id != v2)
                            auxV2 = auxV2->next;
                    }

                    aresta *a1;
                    aresta *a2;
                    
                    
                    if ((auxV1->a == NULL) && (auxV2->a == NULL)){
                        
                        auxV1->a = (aresta*)calloc(1, sizeof(aresta));
                        auxV1->a->aid = v2;
                        auxV1->a->p = peso;

                        auxV2->a = (aresta*)calloc(1, sizeof(aresta));
                        auxV2->a->aid = v1;
                        auxV2->a->p = peso;                        

                    }

                    else if ((auxV1->a != NULL) && (auxV2->a == NULL)){
                        a1 = auxV1->a;

                        while(a1->prox != NULL){                        
                            a1 = a1->prox;
                        }

                        a1->prox = (aresta*)calloc(1, sizeof(aresta));
                        a1->prox->aid = v2;
                        a1->prox->p = peso;

                        auxV2->a = (aresta*)calloc(1, sizeof(aresta));
                        auxV2->a->aid = v1;
                        auxV2->a->p = peso;



                    }

                    else if ((auxV1->a == NULL) && (auxV2->a != NULL)){
                        a2 = auxV2->a;

                        while(a2->prox != NULL){                        
                            a2 = a2->prox;
                        }

                        a2->prox = (aresta*)calloc(1, sizeof(aresta));
                        a2->prox->aid = v1;
                        a2->prox->p = peso;

                        auxV1->a = (aresta*)calloc(1, sizeof(aresta));
                        auxV1->a->aid = v2;
                        auxV1->a->p = peso;
                    }

                    else{
                        a1 = auxV1->a;
                        a2 = auxV2->a;

                        while(a1->prox != NULL){                        
                            a1 = a1->prox;
                        }

                        while(a2->prox != NULL){                        
                            a2 = a2->prox;
                        }

                        a1->prox = (aresta*)calloc(1, sizeof(aresta));
                        a1->prox->aid = v2;
                        a1->prox->p = peso;

                        a2->prox = (aresta*)calloc(1, sizeof(aresta));
                        a2->prox->aid = v1;
                        a2->prox->p = peso;

                    }            
                                

                }
                else
                    printf("pelo menos um dos vertices nao existe\n");
            }
            else
                printf("aresta ja existe\n");
        }
        else
            printf("vertices iguais\n");   
    }
}

void visualizar_grafo(grafo *g){
    if (!grafo_nulo(g)){
        vertice *auxV = g->inicio;
        while (auxV != NULL){
            printf("%d ->", auxV->id);
            aresta *auxA = auxV->a;

            while (auxA != NULL){
                printf(" %d (%d) ->", auxA->aid, auxA->p);
                auxA = auxA->prox;
            }

            printf(" -- \n");

            auxV = auxV->next;
            
        }
    }
    else
        printf("o grafo nao existe\n");

}

int buscar_vert(int id, grafo *g){
    if (!grafo_nulo(g)){
        vertice *auxV = g->inicio;
        while (auxV != NULL){
            if (id == auxV->id)
                return 1;
            auxV = auxV->next;
        }
    }
    return 0;
}

int buscar_aresta(int v1, int v2, grafo *g){
    if (buscar_vert(v1, g) && buscar_vert(v2, g)){
        vertice *auxV = g->inicio;

        while (auxV->id != v1)
            auxV = auxV->next;
        
        aresta *auxA = auxV->a;

        while (auxA != NULL){
            if (auxA->aid == v2)
                return 1;
            auxA = auxA->prox;
        }
            
    }

    return 0;
}

void remover_vertices(int id, grafo *g){
    if (!grafo_nulo(g)){
        if (buscar_vert(id, g)){
            vertice *vProx = g->inicio;
            vertice *vAnt = NULL; 
            
            while (vProx->id != id){
                vAnt = vProx;
                vProx = vProx->next;
            }

            if (vProx->a != NULL){
                aresta *aAux = vProx->a;

                while (aAux != NULL){
                    remover_aresta(aAux->aid, vProx->id, g);
                    aAux = aAux->prox;
                }
            }    

            if (vAnt == NULL){
                if (vProx->next == NULL)
                    g->inicio = NULL;
                
                else
                    g->inicio = vProx->next;
            }
            else{
                if (vProx->next == NULL)
                    vAnt->next = NULL;
                
                else
                    vAnt->next = vProx->next;
            }

            free(vProx);
        }
        else
            printf("o vertice nao existe\n");
    }
}

void remover_aresta(int v1, int v2, grafo *g){
    if (!grafo_nulo(g)){
        if (buscar_aresta(v1, v2, g)){
            vertice *auxV1 = g->inicio;
            vertice *auxV2 = g->inicio;

            while ((auxV1->id != v1) || (auxV2->id != v2)){
                if(auxV1->id != v1)
                    auxV1 = auxV1->next;
                
                if (auxV2->id != v2)
                    auxV2 = auxV2->next;
            }

            aresta *agora1 = NULL;
            aresta *agora2 = NULL;

            aresta *proxima1 = auxV1->a;
            aresta *proxima2 = auxV2->a;

            while (proxima1->aid != v2){
                agora1 = proxima1;
                proxima1 = proxima1->prox;
            }

            while (proxima2->aid != v1){
                agora2 = proxima2;
                proxima2 = proxima2->prox;
            }


            if (agora1 == NULL){
                if (proxima1->prox == NULL)
                    auxV1->a = NULL;
                else
                    auxV1->a = proxima1->prox;
            }
            else{
                if (proxima1->prox == NULL)
                    agora1->prox = NULL;
                else
                    agora1->prox = proxima1->prox;
            }

            if (agora2 == NULL){
                if (proxima2->prox == NULL)
                    auxV2->a = NULL;
                else
                    auxV2->a = proxima2->prox;
            }
            else{
                if (proxima2->prox == NULL)
                    agora2->prox = NULL;
                else
                    agora2->prox = proxima2->prox;
            }

            printf("removida a aresta (%d, %d)", proxima1->aid, proxima2->aid);
            free(proxima1);
            
            free(proxima2);

        }
        else
            printf("a aresta nao existe\n");
    }
    
}


int informa_grau(int v1, int v2, grafo *g){

    if (buscar_vert(v1, g) && buscar_vert(v2, g)){
        vertice *auxV = g->inicio;

        while (auxV->id != v1)
            auxV = auxV->next;
        
        aresta *auxA = auxV->a;

        while (auxA != NULL){
            if (auxA->aid == v2)
                return auxA->p;
            auxA = auxA->prox;
        }
            
    }

    return -1;
}

int qtd_v(grafo *g){ // não colocado no cabeçalho
    if (!grafo_nulo(g)){
        int v;
        vertice *auxV = g->inicio;
        while (auxV != NULL){
            v = auxV->id;
            auxV = auxV->next;
        }
        return v;
    }

    return 0;
}

int qtd_a(grafo *g){ // não colocado no cabeçalho
    if (!grafo_nulo(g)){
        int a=0;
        int v = qtd_v(g);
        for (int i=1; i < v; i++){
            for (int j=i+1; j <= v; j++){
                if (buscar_aresta(i, j, g))
                    a++;
            }
        }

        return a;
    }
    return 0;
}

int grafo_conexo(grafo *g){
    if(!grafo_nulo(g)){
        int qv;
        qv = qtd_v(g);

        int *v = (int*)calloc(qv, sizeof(int));

        vertice *auxV = g->inicio;

        busca_em_profundidade(auxV, v, g);

        for (int i=0; i < qv; i++){
            if (v[i] == 0)
                return 0;
        }

    }
    return 1;
}

void conv_mat_adj(grafo *g);

int busca_em_profundidade(vertice *v, int *verticesVisitados, grafo *g){
    if (v == NULL || verticesVisitados[v->id - 1]) {
        return 1;
    }
    else{
        verticesVisitados[v->id - 1] = 1;
        aresta *aux = v->a; 
        
        while (aux != NULL) {
            vertice *busca = g->inicio;

            while (busca != NULL && busca->id != aux->aid){
                busca = busca->next;
            }
            busca_em_profundidade(busca, verticesVisitados, g);
            aux = aux->prox;
        }
        return 0;
    }
}